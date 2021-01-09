#ifndef NaI_Detector_H
#define NaI_Detector_H 1

#include "G4Material.hh"
#include "Materials.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4PVDivision.hh"

#include "TrackerGammaSD.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4SubtractionSolid.hh"

#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "Randomize.hh"
#include "globals.hh"
#include <iostream>
#include <iomanip>

using namespace std;

class NaI_Detector 
{
public:

  G4LogicalVolume *expHall_log;
  Materials* materials;
  
  NaI_Detector(G4LogicalVolume*, Materials*);
  ~NaI_Detector();

  G4VPhysicalVolume *Construct();

  void setX(G4double x);
  void setY(G4double y);
  void setZ(G4double z);

  void PlaceDetector();
  void MakeSensitive(TrackerGammaSD*);

  private:

  // Logical volumes

  G4LogicalVolume* detector_log;
  G4LogicalVolume* can_log;
  G4LogicalVolume* cap_log;
  G4LogicalVolume* pmt_log;

  // Physical volumes
 
  G4VPhysicalVolume* detector_phys;
  G4VPhysicalVolume* can_phys;
  G4VPhysicalVolume* cap_phys;
  G4VPhysicalVolume* pmt_phys;

  // Materials
  G4Material* NaI;
  G4Material* Al;
  G4Material* pmtMat;

  // dimensions
  G4double Length;
  G4double Radius;
  G4double CanThickness;
  G4double CanInnerRadius;
  G4double CanOuterRadius;
  G4double CanLength;
  G4double pmtRadius;
  G4double pmtLength;

  G4double startAngle;
  G4double spanningAngle;

  // position
  G4RotationMatrix DetRot;
  G4ThreeVector detShift;
  G4ThreeVector DetPos;
  G4ThreeVector pmtShift;
  G4ThreeVector pmtPos;
  G4ThreeVector canShift;
  G4ThreeVector capShift;
  G4ThreeVector canPos;
  G4ThreeVector capPos;
  G4double thetad;
  G4double phid;

  G4Tubs* can;
  G4Tubs* cap;
  G4Tubs* pmt;
  G4Tubs* detector;

};

#endif

