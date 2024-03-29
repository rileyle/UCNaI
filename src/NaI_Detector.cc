#include "NaI_Detector.hh"

NaI_Detector::NaI_Detector(G4LogicalVolume* experimentalHall_log,
			   Materials* mat)
{
  materials=mat;
  expHall_log=experimentalHall_log;

  NaI = materials->FindMaterial("G4_SODIUM_IODIDE");
  Al = materials->FindMaterial("Al");
  pmtMat = materials->FindMaterial("pmtMat");

  Length=2*2.54*cm;
  Radius =1.0*2.54*cm;

  startAngle      = 45.*deg;
  spanningAngle   = 360.*deg;

  CanThickness   = 0.0508*cm;
  CanOuterRadius = 2.54*2.1875/2.0*cm;   //
  CanInnerRadius = CanOuterRadius - CanThickness;
  CanLength      = Length + CanThickness;

  DetPos.setX(0);
  DetPos.setY(0);
  DetPos.setZ(0);

  canShift.setX(0);
  canShift.setY(0);
  canShift.setZ(1.5*CanThickness);
  canPos = DetPos + canShift;

  capShift.setX(0);
  capShift.setY(0);
  capShift.setZ(-CanLength/2.0 - CanThickness/2.0);

  capPos = canPos + capShift;

  detShift.setX(0);
  detShift.setY(0);
  detShift.setZ(2.0*CanThickness);
  DetPos = DetPos + detShift;
  
  pmtRadius      = CanOuterRadius;
  pmtLength      = 5.125*2.54*cm;        // CHECK THIS

  pmtShift.setX(0);
  pmtShift.setY(0);
  pmtShift.setZ(3);
  pmtShift.setMag(Length/2.0 + pmtLength/2.0);
  pmtPos = DetPos + pmtShift;

  thetad = 90.*deg;
  phid = 90.*deg;

  DetRot=G4RotationMatrix::IDENTITY;
  DetRot.rotateX(180.*deg);
  DetRot.rotateY(90.*deg+thetad);
  DetRot.rotateZ(phid);

  assemblyRot = G4RotationMatrix::IDENTITY;
  assemblyRot.rotateX(-90.*deg);

  assemblyPos.setX(0);
  assemblyPos.setY(0);
  assemblyPos.setZ(20*cm);
  
  assembly    = new G4AssemblyVolume();

  geoFileName = "";
}

NaI_Detector::~NaI_Detector()
{
}

void NaI_Detector::Construct()
{

  // Material surrounding the crystal
  can = new G4Tubs("Can",CanInnerRadius,CanOuterRadius,CanLength/2.0,startAngle,spanningAngle);

  can_log = new G4LogicalVolume(can,Al,"can_log",0,0,0);

  cap = new G4Tubs("Cap",0.,CanOuterRadius,CanThickness/2.0,startAngle,spanningAngle);

  cap_log = new G4LogicalVolume(cap,Al,"cap_log",0,0,0);

  pmt = new G4Tubs("pmt",0.,pmtRadius,pmtLength/2.0,startAngle,spanningAngle);

  pmt_log = new G4LogicalVolume(pmt,pmtMat,"pmt_log",0,0,0);

  // detector

  detector = new G4Tubs("detector",0,Radius,Length/2.0,startAngle,spanningAngle);

  detector_log = new G4LogicalVolume(detector,NaI,"detector_log",0,0,0);

  PlaceDetector();

 //------------------------------Detector readout division

  //Visualization Attributes

  //   NaI Crystal
  G4Colour dgreen (0.0,0.75, 0.0, 1.0); 
  G4VisAttributes* Vis_1 = new G4VisAttributes(dgreen);
  Vis_1->SetVisibility(true);
  Vis_1->SetForceSolid(true);

  //   Can
  G4Colour transGrey (0.5, 0.5, 0.5, 0.3);
  G4VisAttributes* Vis_2 = new G4VisAttributes(transGrey);
  Vis_2->SetVisibility(true);
  Vis_2->SetForceSolid(true);

  //   Dead material
  G4Colour dGrey (0.8, 0.8, 0.8, 1.0);
  G4VisAttributes* Vis_3 = new G4VisAttributes(dGrey);
  Vis_3->SetVisibility(true);
  Vis_3->SetForceSolid(true);

  detector_log->SetVisAttributes(Vis_1);

  can_log->SetVisAttributes(Vis_2);

  cap_log->SetVisAttributes(Vis_2);

  pmt_log->SetVisAttributes(Vis_3);
 
}
//---------------------------------------------------------------------
void NaI_Detector::PlaceDetector()
{

  // detector_phys = new G4PVPlacement(G4Transform3D(DetRot,DetPos),
  //            detector_log,"detector",expHall_log,false,0); 
 
  // can_phys = new G4PVPlacement(G4Transform3D(DetRot,canPos),
  // 			       can_log,"Can",expHall_log,false,0,true);

  // cap_phys = new G4PVPlacement(G4Transform3D(DetRot,capPos),
  // 			       cap_log,"Cap",expHall_log,false,0,true);

  // pmt_phys = new G4PVPlacement(G4Transform3D(DetRot,pmtPos),
  // 			       pmt_log,"PMT",expHall_log,false,0,true);

  assembly->AddPlacedVolume(detector_log, DetPos, &DetRot);

  assembly->AddPlacedVolume(can_log, canPos, &DetRot);

  assembly->AddPlacedVolume(cap_log, capPos, &DetRot);

  assembly->AddPlacedVolume(pmt_log, pmtPos, &DetRot);
  
  // If there is a NaI geometry file, use it for placement,
  // if not, use the curret assemblyPos and assemblyRot to
  // place a single NaI.
  G4int detID = 1000; // Base for the replica number.
  if(geoFileName != ""){
    geoFile.open(geoFileName.c_str());
    if (!geoFile.is_open())
      G4cout<< "ERROR opening NaI geometry file." << G4endl;
    else
      G4cout << "\nPositioning NaI detectors using the geometry file: " << geoFileName << G4endl;

    G4double x, y, z, ax, ay, az;
    while(geoFile >> x >> y >> z >> ax >> ay >> az){
      assemblyPos.setX(x);
      assemblyPos.setY(y);
      assemblyPos.setZ(z);
      assemblyRot = G4RotationMatrix::IDENTITY;
      assemblyRot.rotateX(ax*deg);
      assemblyRot.rotateY(ay*deg);
      assemblyRot.rotateZ(az*deg);
      assembly->MakeImprint(expHall_log, assemblyPos, &assemblyRot, detID);
      detID++;
    }
  } else {
    assembly->MakeImprint(expHall_log, assemblyPos, &assemblyRot, detID);
  }
}
//---------------------------------------------------------------------
void NaI_Detector::MakeSensitive(TrackerGammaSD* TrackerGamma)
{
  detector_log->SetSensitiveDetector(TrackerGamma);
}
//---------------------------------------------------------------------
