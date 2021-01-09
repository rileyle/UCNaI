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
  void SetSource(){source=true;inbeam=false;};
  void SetSourceX(G4double);
  void SetSourceY(G4double);
  void SetSourceZ(G4double);
  void SourceReport();
  void SetSourceType(G4String name);
  void SetSourceEu152();
  void SetSourceCs137();
  void SetSourceCo56();
  void SetSourceCo60();
  void SetSourceAu();
  void SetSourceSimple();
  G4double GetSourceEnergy();
  void SetSourceEnergy(G4double);
  DetectorConstruction* getDetectorConstruction(){return myDetector;};

private:

  G4int n_particle;
  G4ParticleGun* particleGun;
  G4ParticleTable* particleTable;

  G4ThreeVector  direction;
  G4ThreeVector  position;
  G4double       KE;
  DetectorConstruction* myDetector;

  // source stuff
  G4bool source,inbeam; 
  G4String sourceType;  //LR
  G4ThreeVector sourcePosition;
  vector<SourceData*> TheSource;
  G4double sourceBranchingSum;
};


#endif


           
