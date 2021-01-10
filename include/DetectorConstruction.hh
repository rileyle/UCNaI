#ifndef DetectorConstruction_H
#define DetectorConstruction_H 1

#include "G4VUserDetectorConstruction.hh"
#include "Materials.hh"
#include "Experimental_Hall.hh"
#include "Experimental_Hall_Messenger.hh"
#include "NaI_Detector.hh"
#include "NaI_Detector_Messenger.hh"
#include "Lead_Brick.hh"
#include "Lead_Brick_Messenger.hh"
#include "Target.hh"
#include "Target_Messenger.hh"
#include "Source_Capsule.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "TrackerGammaSD.hh"
#include "TrackerGammaSD_Messenger.hh"
#include "G4SDManager.hh"
#include "G4Tubs.hh"

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:

  DetectorConstruction();
  ~DetectorConstruction();

  G4VPhysicalVolume* Construct();
  Source_Capsule* getSourceCapsule(){return capsule;};
  G4LogicalVolume* HallLog(){return ExpHall_log;};

private:
  
  NaI_Detector* the_NaI_Detector;

  Source_Capsule* capsule;
  Lead_Brick* brick;
  Target* target;

  // Logical volumes
  G4LogicalVolume* ExpHall_log;

  // Physical volumes
  G4VPhysicalVolume* ExpHall_phys;

  Experimental_Hall_Messenger* ExperimentalHallMessenger;
  TrackerGammaSD* TrackerGamma;
  TrackerGammaSD_Messenger* TrackerGammaSDMessenger;
  NaI_Detector_Messenger* the_NaI_Detector_Messenger;
  Lead_Brick_Messenger* brick_Messenger;
  Target_Messenger* target_Messenger;

  Materials* materials;
};

#endif
