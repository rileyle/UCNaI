#include "NaI_Array.hh"

NaI_Array::NaI_Array(G4LogicalVolume* experimentalHall_log,
		     Materials* mat)
{
  materials=mat;
  expHall_log=experimentalHall_log;

  assemblyRot = G4RotationMatrix::IDENTITY;
  assemblyRot.rotateX(-90.*deg);

  assemblyPos.setX(0);
  assemblyPos.setY(0);
  assemblyPos.setZ(20*cm);

  detector_2x2 = NULL;
  detector_3x3 = NULL;
  
  detectorType = "2x2";
  
  geoFileName = "";
}

NaI_Array::~NaI_Array()
{
}

//---------------------------------------------------------------------
void NaI_Array::Construct()
{
  // If there is a NaI geometry file, use it for placement,
  // if not, use the curret assemblyPos and assemblyRot to
  // place a single NaI.
  G4int detID = 1000; // Base for the replica number.
  if(geoFileName != ""){
    geoFile.open(geoFileName.c_str());
    if (!geoFile.is_open()){
      G4cout<< "ERROR opening NaI geometry file." << G4endl;
      exit (EXIT_FAILURE);
    } else
      G4cout << "\nPositioning NaI detectors using the geometry file: " << geoFileName << G4endl;
    
    G4String type;
    G4double x, y, z, ax, ay, az;
    while(geoFile >> type >> x >> y >> z >> ax >> ay >> az){
      assemblyPos.setX(x);
      assemblyPos.setY(y);
      assemblyPos.setZ(z);
      assemblyRot = G4RotationMatrix::IDENTITY;
      assemblyRot.rotateX(ax*deg);
      assemblyRot.rotateY(ay*deg);
      assemblyRot.rotateZ(az*deg);
      if(type.contains("2x2")){
	if(detector_2x2 == NULL){
	  detector_2x2 = new NaI_2x2_Detector(expHall_log, materials);
	  detector_2x2->Construct();
	}
	detector_2x2->GetAssembly()->MakeImprint(expHall_log, assemblyPos, &assemblyRot, detID);
      } else if(type.contains("3x3")){
	if(detector_3x3 == NULL){
	  detector_3x3 = new NaI_3x3_Detector(expHall_log, materials);
	  detector_3x3->Construct();
	}
	detector_3x3->GetAssembly()->MakeImprint(expHall_log, assemblyPos, &assemblyRot, detID);
      }else {
	G4cout<< "ERROR: unrecognized detector type" << type.c_str()
	      << G4endl;
	exit (EXIT_FAILURE);
      }

      detID++;
    }
  } else {
    if(detectorType.contains("2x2")){
      detector_2x2 = new NaI_2x2_Detector(expHall_log, materials);
      detector_2x2->Construct();
      detector_2x2->GetAssembly()->MakeImprint(expHall_log, assemblyPos, &assemblyRot, detID);
    } else if(detectorType.contains("3x3")){
      detector_3x3 = new NaI_3x3_Detector(expHall_log, materials);
      detector_3x3->Construct();
      detector_3x3->GetAssembly()->MakeImprint(expHall_log, assemblyPos, &assemblyRot, detID);
    } else {
	G4cout<< "ERROR: unrecognized detector type" << detectorType
	      << G4endl;
	exit (EXIT_FAILURE);
    }
  }
}
//---------------------------------------------------------------------
void NaI_Array::MakeSensitive(TrackerGammaSD* TG){

  if(detector_2x2 != NULL)
    detector_2x2->MakeSensitive(TG);
  
  if(detector_3x3 != NULL)
    detector_3x3->MakeSensitive(TG);

}
//---------------------------------------------------------------------
