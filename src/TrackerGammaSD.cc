
#include "TrackerGammaSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4UnitsTable.hh"
#include "G4VTouchable.hh"
#include <string.h>
#include <stdio.h>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TrackerGammaSD::TrackerGammaSD(G4String name)
:G4VSensitiveDetector(name)
{
  G4String HCname;
  collectionName.insert(HCname="gammaCollection");
  print=false; //LR (formerly not initialized)

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TrackerGammaSD::~TrackerGammaSD(){ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TrackerGammaSD::Initialize(G4HCofThisEvent*)
{


  gammaCollection = new TrackerGammaHitsCollection
                          (SensitiveDetectorName,collectionName[0]); 
 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool TrackerGammaSD::ProcessHits(G4Step* aStep,G4TouchableHistory*)
{

  G4double DE = aStep->GetTotalEnergyDeposit();
  if(DE<0.001*eV) return false;

  G4double edep = aStep->GetTotalEnergyDeposit();
  G4double etotal = aStep->GetPreStepPoint()->GetTotalEnergy();
  G4String name
    = aStep->GetPostStepPoint()->GetTouchable()->GetVolume()->GetName(); 
  G4int detID
    = aStep->GetPostStepPoint()->GetTouchable()->GetReplicaNumber(0)-1000;
  
  if(name.contains("detector"))
    {

      TrackerGammaHit* newHit = new TrackerGammaHit();

      newHit->SetTrackID  (aStep->GetTrack()->GetTrackID());

      newHit->SetParticleID(aStep->GetTrack()->GetDefinition()->GetParticleName());
      newHit->SetDetID    (detID); // Coming real soon now.
      newHit->SetEdep     (edep);
      newHit->SetTotalEnergy(etotal);
      newHit->SetPos      (aStep->GetPostStepPoint()->GetPosition());

      gammaCollection->insert( newHit );
      newHit->Draw();

      //  newHit->Print(); 

      return true;
    }
  else
    {
      //G4cout << "Energy deposit in the " << name << G4endl;
      //G4cout << "E="<<G4BestUnit(edep,"Energy")<<G4endl;
      //G4cout <<"Event ignored" <<G4endl;

      return false;
    }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TrackerGammaSD::EndOfEvent(G4HCofThisEvent* HCE)
{
   G4int i;
   G4int NbHits = gammaCollection->entries();

        if (NbHits>0&&print) 
	   { 
	    
	   G4cout << "\n--------> " << NbHits << " hits for gamma tracking: " << G4endl;

	   for (i=0;i<NbHits;i++) (*gammaCollection)[i]->Print();

	   }


  static G4int HCID = -1;
  if(HCID<0)
  { HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]); }
  HCE->AddHitsCollection( HCID, gammaCollection ); 
 }


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

