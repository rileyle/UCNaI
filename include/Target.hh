#ifndef Target_H
#define Target_H 1

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

class Target
{
public:

  G4LogicalVolume *expHall_log;
  Materials* materials;
  
  Target(G4LogicalVolume*, Materials*);
  ~Target();

  void Construct();

  void setX(G4double);
  void setY(G4double);
  void setZ(G4double);

  void rotateX(G4double);
  void rotateY(G4double);
  void rotateZ(G4double);
  void setGeoFile(G4String fname){geoFileName = fname;}

  void setR(G4double r){Radius = r;}
  void setL(G4double l){Length = l;}
  
  G4double getLength(){return Length;};
  G4double getRadius(){return Radius;};

  void PlaceTarget();

  private:

  // Logical volume

  G4LogicalVolume* target_log;

  // Physical volume
 
  //  G4VPhysicalVolume* target_phys;

  // Materials
  G4Material* Al;

  // dimensions
  G4double Length;
  G4double Radius;

  // position
  G4RotationMatrix Rot;
  G4ThreeVector Pos;

  G4Tubs* target;

  G4String geoFileName;
  std::ifstream geoFile;
};

#endif

