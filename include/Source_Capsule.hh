#ifndef Source_Capsule_H
#define Source_Capsule_H 1

#include "G4Material.hh"
#include "Materials.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "Randomize.hh"
#include "globals.hh"
#include <iostream>
#include <iomanip>

using namespace std;

class Source_Capsule
{
public:

  G4LogicalVolume *expHall_log;
  Materials* materials;
  
  Source_Capsule(G4LogicalVolume*, Materials*);
  ~Source_Capsule();

  G4VPhysicalVolume *Construct();
  void setX(G4double);
  void setY(G4double);
  void setZ(G4double);

  void rotateX(G4double);
  void rotateY(G4double);
  void rotateZ(G4double);

  G4double getDepth(){return Depth;};
  G4double getRadius(){return Radius;};
  void PlaceCapsule();

  private:

  // Logical volume

  G4LogicalVolume* capsule_log;

  // Physical volume
 
  G4VPhysicalVolume* capsule_phys;

  // Materials
  G4Material* polyethylene;

  // dimensions
  G4double Depth;
  G4double Radius;
  G4double innerRadius;
  G4double startAngle;
  G4double spanningAngle;

  // position
  G4RotationMatrix Rot;
  G4ThreeVector Pos;

  G4Tubs* capsule;

};

#endif

