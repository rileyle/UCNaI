#include "NaI_3x3_Detector.hh"

NaI_3x3_Detector::NaI_3x3_Detector(G4LogicalVolume* experimentalHall_log,
			   Materials* mat)
{
  materials=mat;
  expHall_log=experimentalHall_log;

  NaI = materials->FindMaterial("G4_SODIUM_IODIDE");
  Al = materials->FindMaterial("Al");
  pmtMat = materials->FindMaterial("pmtMat");

  Length=7.5*cm;
  Radius =3.75*cm;

  startAngle      = 45.*deg;
  spanningAngle   = 360.*deg;

  CanThickness   = 0.0508*cm;
  CanOuterRadius = 4*cm;   //
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
  pmtLength      = 15*cm;      

  pmtShift.setX(0);
  pmtShift.setY(0);
  pmtShift.setZ(3);
  pmtShift.setMag(Length/2.0 );   //removed +pmtlength/2.0
  
  pmtPos = DetPos + pmtShift;

  thetad = 90.*deg;
  phid = 90.*deg;

  DetRot=G4RotationMatrix::IDENTITY;
  DetRot.rotateX(180.*deg);
  DetRot.rotateY(90.*deg+thetad);
  DetRot.rotateZ(phid);

  assembly    = new G4AssemblyVolume();

}

NaI_3x3_Detector::~NaI_3x3_Detector()
{
}

void NaI_3x3_Detector::Construct()
{

  // Material surrounding the crystal
  can = new G4Tubs("Can", CanInnerRadius, CanOuterRadius, CanLength/2.0,
		   startAngle, spanningAngle);

  can_log = new G4LogicalVolume(can, Al, "can_log", 0, 0, 0);

  cap = new G4Tubs("Cap", 0., CanOuterRadius, CanThickness/2.0,
		   startAngle, spanningAngle);

  cap_log = new G4LogicalVolume(cap, Al, "cap_log", 0, 0, 0);

  // pmt = new G4Tubs("pmt",0.,pmtRadius,pmtLength/2.0,startAngle,spanningAngle);


  // G4Tubs to G4Polycone
  const G4double zPlane[4] = {0, 3.2*cm, 4.3*cm, 12.7*cm}; //should the fourth value have an extra .84 cm on it

  const G4double rInner[4] = {0, 0, 0, 0};

  const G4double rOuter[4] = {4*cm, 4*cm,3*cm , 3*cm};
   

  pmt = new G4Polycone("pmt", startAngle, spanningAngle, 4, zPlane, rInner, rOuter);

  pmt_log = new G4LogicalVolume(pmt,pmtMat,"pmt_log",0,0,0);

  // detector

  detector = new G4Tubs("detector",0,Radius,Length/2.0,startAngle,spanningAngle);

  detector_log = new G4LogicalVolume(detector,NaI,"detector_log",0,0,0);

  assembly->AddPlacedVolume(detector_log, DetPos, &DetRot);

  assembly->AddPlacedVolume(can_log, canPos, &DetRot);

  assembly->AddPlacedVolume(cap_log, capPos, &DetRot);

  assembly->AddPlacedVolume(pmt_log, pmtPos, &DetRot);

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
void NaI_3x3_Detector::MakeSensitive(TrackerGammaSD* TrackerGamma)
{
  detector_log->SetSensitiveDetector(TrackerGamma);
}
//---------------------------------------------------------------------
