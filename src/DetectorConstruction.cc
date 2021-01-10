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

  // NaI Detector

  the_NaI_Detector = new NaI_Detector(ExpHall_log, materials);
  the_NaI_Detector_Messenger = new NaI_Detector_Messenger(the_NaI_Detector);  

  // Source Capsule

  capsule = new Source_Capsule(ExpHall_log, materials);
  //  Capsule->setX(0.0*cm);
  //  Capsule->setY(Capsule->getDepth()/2.0);
  //  Capsule->setZ(0.0*cm);
  //  Capsule->setTheta(90.0*deg);
  //  Capsule->setPhi(90.0*deg);
  // Don't automatically construct -- only via the messenger.
  //  Capsule->Construct();
  // Lead Brick

  brick = new Lead_Brick(ExpHall_log, materials);
  // Don't automatically construct -- only via the messenger.
  // Brick->Construct();

  brick_Messenger = new Lead_Brick_Messenger(brick);  

  target = new Target(ExpHall_log, materials);
  // Don't automatically construct -- only via the messenger.
  // Target->Construct();

  target_Messenger = new Target_Messenger(target);
}

DetectorConstruction::~DetectorConstruction()
{
  delete ExperimentalHallMessenger;
  delete TrackerGammaSDMessenger;

}

G4VPhysicalVolume* DetectorConstruction::Construct()
{

  the_NaI_Detector->Construct();
  
  //------------------------------------------------ 
  // Sensitive detectors
  //------------------------------------------------ 

  G4SDManager* SDman = G4SDManager::GetSDMpointer();

  //------------------------------------------------
  // Detectors sensitive for gamma-ray tracking
  //-------------------------------------------------

  TrackerGamma = new TrackerGammaSD("GammaTracker" );
  TrackerGammaSDMessenger = new TrackerGammaSD_Messenger(TrackerGamma);
  SDman->AddNewDetector( TrackerGamma );
  the_NaI_Detector->MakeSensitive(TrackerGamma);

  return ExpHall_phys;
}
