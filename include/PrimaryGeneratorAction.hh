#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ThreeVector.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "DetectorConstruction.hh"
#include "Randomize.hh"
#include "G4RandomDirection.hh"
#include <vector>
#include "SourceData.hh"

using namespace std;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  PrimaryGeneratorAction(DetectorConstruction*);
  ~PrimaryGeneratorAction();
  
public:
  void GeneratePrimaries(G4Event* anEvent);
  void SetSourceX(G4double);
  void SetSourceY(G4double);
  void SetSourceZ(G4double);
  void SourceReport();
  void SetSourceEnergy(G4double);
  DetectorConstruction* getDetectorConstruction(){return myDetector;};

private:

  G4int n_particle;
  G4ParticleGun* particleGun;
  G4ParticleTable* particleTable;

  DetectorConstruction* myDetector;

  // source stuff
  G4String sourceType;
  G4ThreeVector sourcePosition;
  G4double simpleSourceEnergy;
};


#endif


           
