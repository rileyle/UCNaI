
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
  
      void SetTrackID  (G4int track)      { trackID = track; };
      void SetParticleID (G4String particle)      { particleID = particle; };
      void SetDetNumb(G4int num) {detNumb=num;};
      void SetRingID(G4int num) {ringID=num;};
      void SetSliceNbi(G4int slicei)   { sliceNbi = slicei; };  
      void SetQuartNbi(G4int quarti)   { quartNbi = quarti; };  
      void SetSliceNbf(G4int slicef)   { sliceNbf = slicef; };  
      void SetQuartNbf(G4int quartf)   { quartNbf = quartf; };  
      void SetEdep     (G4double de)      { edep = de; };
      void SetTotalEnergy(G4double te)      { etotal = te; }; //LR
      void SetPos      (G4ThreeVector xyz){ pos = xyz; };
      
      G4int GetTrackID()    { return trackID; };
      G4String GetParticleID() {return particleID;};
      G4int  GetDetNumb() {return detNumb;};
      G4int  GetRingID() {return ringID;};
      G4int  GetSliceNbi()  { return sliceNbi; };
      G4int  GetQuartNbi()  { return quartNbi; };
      G4int  GetSliceNbf()  { return sliceNbf; };
      G4int  GetQuartNbf()  { return quartNbf; }; 
      G4double GetEdep()    { return edep; };
      G4double GetTotalEnergy() { return etotal; }; //LR
      G4ThreeVector GetPos(){ return pos; };
      
  private:
  
      G4int         trackID;
      G4String      particleID;
      G4int         detNumb;
      G4int         ringID;
      G4int         sliceNbi;
      G4int         quartNbi;
      G4int         sliceNbf;
      G4int         quartNbf;
      G4double      edep;
      G4double      etotal; //LR
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
