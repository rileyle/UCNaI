#ifndef Experimental_Hall_H
#define Experimental_Hall_H 1


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
#include "G4UnitsTable.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

class Experimental_Hall 
{
  public:

  Experimental_Hall(Materials*);
  ~Experimental_Hall();
  
  G4VPhysicalVolume *Construct();
  G4LogicalVolume* GetLogVolume(){return ExperimentalHall_log;};
  void setX(G4double);
  void setY(G4double);
  void setZ(G4double);
  void setMaterial(G4String);
  void Report();
  
    private:
  // dimensions
  G4double expHall_x;
  G4double expHall_y;
  G4double expHall_z;

  //materials
  Materials* materials;
  G4Material* ExperimentalHallMaterial;

  //the box
  G4Box* ExperimentalHall;

  //logical volume
  G4LogicalVolume* ExperimentalHall_log;
 
  //physical volume
  G4VPhysicalVolume* ExperimentalHall_phys;
 

};

#endif

