#ifndef EventInformation_h
#define EventInformation_h 1

#include "G4VUserEventInformation.hh"
#include "G4ThreeVector.hh"
#include "G4SystemOfUnits.hh"

#define MAX_SIM_GAMMAS 10       /* max. simulated gammas per event */

class EventInformation : public G4VUserEventInformation
{
public:

  EventInformation();
  ~EventInformation(){};

  inline virtual void Print()const{;}

  void AddEmittedGamma(G4double, G4ThreeVector*, G4ThreeVector*, G4int);
  void SetFullEnergy(G4int f){ fFullEnergy = f; }

  G4double GetEmittedGammaEnergy(G4int i){ return fEmittedGammaEnergies[i]; }
  G4double GetEmittedGammaPosX(G4int i){ return fEmittedGammaPosX[i]; }
  G4double GetEmittedGammaPosY(G4int i){ return fEmittedGammaPosY[i]; }
  G4double GetEmittedGammaPosZ(G4int i){ return fEmittedGammaPosZ[i]; }
  G4double GetEmittedGammaPhi(G4int i){ return fEmittedGammaPhi[i]; }
  G4double GetEmittedGammaTheta(G4int i){ return fEmittedGammaTheta[i]; }
  G4int GetNEmittedGammas(){return fNEmittedGammas;}
  G4int GetFullEnergy(){ return fFullEnergy; }

private:

  G4double fEmittedGammaEnergies[MAX_SIM_GAMMAS];
  G4double fEmittedGammaPosX[MAX_SIM_GAMMAS];
  G4double fEmittedGammaPosY[MAX_SIM_GAMMAS];
  G4double fEmittedGammaPosZ[MAX_SIM_GAMMAS];
  G4double fEmittedGammaPhi[MAX_SIM_GAMMAS];
  G4double fEmittedGammaTheta[MAX_SIM_GAMMAS];
  G4int    fNEmittedGammas;
  G4int    fFullEnergy;
};

#endif
