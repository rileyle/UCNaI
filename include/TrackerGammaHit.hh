
#ifndef TrackerGammaHit_h
#define TrackerGammaHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4SystemOfUnits.hh"
#include <iomanip>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class TrackerGammaHit : public G4VHit
{
  public:

      TrackerGammaHit();
     ~TrackerGammaHit();
      TrackerGammaHit(const TrackerGammaHit&);
      const TrackerGammaHit& operator=(const TrackerGammaHit&);
      G4int operator==(const TrackerGammaHit&) const;

      inline void* operator new(size_t);
      inline void  operator delete(void*);

      void Draw();
      void Print();

  public:
  
      void SetTrackID  (G4int track)        { trackID = track; };
      void SetParticleID (G4String particle){ particleID = particle; };
      void SetDetID(G4int id)               { detID = id; };
      void SetEdep     (G4double de)        { edep = de; };
      void SetTotalEnergy(G4double te)      { etotal = te; };
      void SetPos      (G4ThreeVector xyz)  { pos = xyz; };
      
      G4int GetTrackID()       { return trackID; };
      G4String GetParticleID() { return particleID; };
      G4int  GetDetID()        { return detID; };
      G4double GetEdep()       { return edep; };
      G4double GetTotalEnergy(){ return etotal; };
      G4ThreeVector GetPos()   { return pos; };
      
  private:
  
      G4int         trackID;
      G4String      particleID;
      G4int         detID;
      G4double      edep;
      G4double      etotal;
      G4ThreeVector pos;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

typedef G4THitsCollection<TrackerGammaHit> TrackerGammaHitsCollection;

extern G4Allocator<TrackerGammaHit> TrackerGammaHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void* TrackerGammaHit::operator new(size_t)
{
  void *aHit;
  aHit = (void *) TrackerGammaHitAllocator.MallocSingle();
  return aHit;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void TrackerGammaHit::operator delete(void *aHit)
{
  TrackerGammaHitAllocator.FreeSingle((TrackerGammaHit*) aHit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
