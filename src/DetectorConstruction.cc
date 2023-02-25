#include "DetectorConstruction.hh"

DetectorConstruction::DetectorConstruction()
{

  //  Materials* materials=new Materials();
  materials=new Materials();

  // Experimental Hall

  Experimental_Hall* ExperimentalHall = new Experimental_Hall(materials);
  ExpHall_phys=ExperimentalHall->Construct();
  ExpHall_log=ExperimentalHall->GetLogVolume();
  //   ExperimentalHall->Report();
  ExperimentalHallMessenger = new Experimental_Hall_Messenger(ExperimentalHall);
  
  // NaI Array

  the_NaI_Array = new NaI_Array(ExpHall_log, materials);
  the_NaI_Array_Messenger = new NaI_Array_Messenger(the_NaI_Array);

  // Source Capsule

  capsule = new Source_Capsule(ExpHall_log, materials);
  capsule_Messenger = new Source_Capsule_Messenger(capsule);
  
  brick = new Lead_Brick(ExpHall_log, materials);

  brick_Messenger = new Lead_Brick_Messenger(brick);  

  target = new Target(ExpHall_log, materials);

  target_Messenger = new Target_Messenger(target);
  
}

DetectorConstruction::~DetectorConstruction()
{
  delete ExperimentalHallMessenger;
  delete TrackerGammaSDMessenger;

}

G4VPhysicalVolume* DetectorConstruction::Construct()
{

  the_NaI_Array->Construct();

  //------------------------------------------------ 
  // Sensitive detectors
  //------------------------------------------------ 

  G4SDManager* SDman = G4SDManager::GetSDMpointer();

  //------------------------------------------------
  // Detectors sensitive for gamma-ray tracking
  //-------------------------------------------------

  TrackerGamma = new TrackerGammaSD("GammaTracker");
  TrackerGammaSDMessenger = new TrackerGammaSD_Messenger(TrackerGamma);
  SDman->AddNewDetector(TrackerGamma);
  the_NaI_Array->MakeSensitive(TrackerGamma);
  
  return ExpHall_phys;

}
