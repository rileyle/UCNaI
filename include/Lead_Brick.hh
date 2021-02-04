#ifndef Lead_Brick_H
#define Lead_Brick_H 1

#include "G4Material.hh"
#include "Materials.hh"
#include "G4Box.hh"
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

class Lead_Brick
{
public:

  G4LogicalVolume *expHall_log;
  Materials* materials;
  
  Lead_Brick(G4LogicalVolume*, Materials*);
  ~Lead_Brick();

  void Construct();

  void setX(G4double);
  void setY(G4double);
  void setZ(G4double);

  void rotateX(G4double);
  void rotateY(G4double);
  void rotateZ(G4double);
  void setGeoFile(G4String fname){geoFileName = fname;}

  G4double getLength(){return Length;};
  G4double getWidth(){return Width;};
  G4double getDepth(){return Depth;};

  void PlaceBrick();

  private:

  // Logical volume

  G4LogicalVolume* brick_log;

  // Physical volume
 
  // G4VPhysicalVolume* brick_phys;

  // Materials
  G4Material* Pb;

  // dimensions
  G4double Length;
  G4double Width;
  G4double Depth;

  // position
  G4RotationMatrix Rot;
  G4ThreeVector Pos;

  G4Box* brick;

  G4String geoFileName;
  std::ifstream geoFile;
};

#endif

