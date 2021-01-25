#include "EventAction.hh"
#include "RunAction.hh"

//EventAction::EventAction(Results* RE): results(RE)
EventAction::EventAction()
{ 
  //  ionCollectionID=-1;
  gammaCollectionID=-1;
}


EventAction::~EventAction()
{
  ;
}

void EventAction::BeginOfEventAction(const G4Event*)
{
 
  G4SDManager * SDman = G4SDManager::GetSDMpointer();

  //  if(gammaCollectionID<0||ionCollectionID<0)
  if(gammaCollectionID<0)
    {
      gammaCollectionID=SDman->GetCollectionID("gammaCollection");
      //      ionCollectionID=SDman->GetCollectionID("ionCollection");
    }

  // G4cout<<"+++++ Begin of event "<<evt->GetEventID()<<G4endl;

}


void EventAction::EndOfEventAction(const G4Event* evt)
{
  // G4cout<<"+++++ End of event "<<evt->GetEventID()<<G4endl;

  G4int event_id=evt->GetEventID();

  if(event_id%10000==0) {
    G4cout<<" Number of processed events "<<event_id<<"\r"<<std::flush;
  }
 
  // Write event information to the output file.
  G4HCofThisEvent * HCE = evt->GetHCofThisEvent();
  if(HCE) {

    TrackerGammaHitsCollection* gammaCollection = (TrackerGammaHitsCollection*)(HCE->GetHC(gammaCollectionID));

    G4int Ngamma = gammaCollection->entries();

    if(Ngamma>0) {

      G4double Edep = 0;
      G4double EdepMax = 0;
      G4int firstHit=0;
      for(int i=0; i<Ngamma; i++) {

	G4double E = (*gammaCollection)[i]->GetEdep()/keV;

	if(E>EdepMax) { 
	  EdepMax = E;
	  firstHit = i;
	}

	Edep += E;

      }

      //      G4cout << "**** Track Total Energy = " << (*gammaCollection)[0]->GetTotalEnergy()/keV << G4endl;

      //      G4cout << "**** Energy Deposited = " << Edep << G4endl;

      G4int photopeak = 0;
      if(abs((*gammaCollection)[0]->GetTotalEnergy()/keV-Edep)<0.001) {
	photopeak = 1;
      }

      evfile
	<< std::setw(15) << std::right
	<< event_id
	<< std::setw(5) << std::right
	<< (*gammaCollection)[firstHit]->GetDetID()
	<< std::fixed << std::setprecision(2) << std::setw(10) << std::right
	<< Edep
	<< std::setw(10) << std::right
	<< (*gammaCollection)[firstHit]->GetPos().getX()/mm
	<< std::setw(10) << std::right
	<< (*gammaCollection)[firstHit]->GetPos().getY()/mm
	<< std::setw(10) << std::right
	<< (*gammaCollection)[firstHit]->GetPos().getZ()/mm
	<< std::setw(10) << std::right
	<< photopeak
	<< G4endl;

    }

  }

}
// --------------------------------------------------TB
void EventAction::openEvfile()
{
  if (!evfile.is_open()) evfile.open(outFileName.c_str());
  if (!evfile.is_open())
    G4cout<< "ERROR opening evfile." << G4endl;
  else
    G4cout << "\nOpened output file: " << outFileName << G4endl;
  return;
}
//--------------------------------------------------- TB
void EventAction::closeEvfile()
{
	evfile.close();
	return;
}
//----------------------------------------------------TB
void EventAction::SetOutFile(G4String name)
{
	outFileName = name;
	closeEvfile();
	openEvfile();
	return;
}
