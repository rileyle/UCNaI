#include "EventAction.hh"
#include "RunAction.hh"

#include "G4Timer.hh"
extern G4Timer Timerintern;

EventAction::EventAction()
{ 
  gammaCollectionID=-1;

  Timerintern.Start();
}


EventAction::~EventAction()
{
  ;
}

void EventAction::BeginOfEventAction(const G4Event* ev)
{
  evt = ev;

  // Add a G4UserEventInformation object to store event info
  EventInformation* eventInfo = new EventInformation;
  G4EventManager::GetEventManager()->SetUserInformation(eventInfo);
 
  G4SDManager * SDman = G4SDManager::GetSDMpointer();

  if(gammaCollectionID<0)
    {
      gammaCollectionID=SDman->GetCollectionID("gammaCollection");
    }

}


void EventAction::EndOfEventAction(const G4Event* ev)
{

  evt = ev;
    
  ios::fmtflags f( G4cout.flags() );

  G4int event_id=evt->GetEventID();

  if(event_id%everyNevents == 0 && event_id > 0) {
    Timerintern.Stop();
    timerCount++;
    eventsPerSecond += 
      ((double)everyNevents/Timerintern.GetRealElapsed() 
       - eventsPerSecond)/timerCount;
    G4cout << std::fixed << std::setprecision(0) << std::setw(3) 
	   << std::setfill(' ')
	   << (float)event_id/NTotalEvents*100 << " %   "
	   << eventsPerSecond << " events/s ";

    G4double hours, minutes, seconds;
    G4double time = (float)(NTotalEvents - event_id)/eventsPerSecond;
    hours = floor(time/3600.0);
    if(hours>0){
      G4cout << std::setprecision(0) << std::setw(2) 
	     << hours << ":";
      G4cout << std::setfill('0');
    } else {
      G4cout << std::setfill(' ');
    }
    minutes = floor(fmod(time,3600.0)/60.0);
    if(minutes>0){
      G4cout << std::setprecision(0) << std::setw(2) << minutes << ":";
      G4cout << std::setfill('0');
    } else {
      G4cout << std::setfill(' ');
    }
    seconds = fmod(time,60.0);
    if(seconds>0)
      G4cout << std::setprecision(0) << std::setw(2) << seconds;
    G4cout << std::setfill(' ');
    G4cout << " remaining       "
	   << "\r"<<std::flush;
    Timerintern.Start();
  }

  EventInformation* eventInfo = (EventInformation*)evt->GetUserInformation();
  
  //  if(event_id%10000==0) {
  //    G4cout<<" Number of processed events "<<event_id<<"\r"<<std::flush;
  //  }
 
  // Write event information to the output file.
  G4HCofThisEvent * HCE = evt->GetHCofThisEvent();
  if(HCE) {

    TrackerGammaHitsCollection* gammaCollection = (TrackerGammaHitsCollection*)(HCE->GetHC(gammaCollectionID));

    G4int Ngamma = gammaCollection->entries();

    if(Ngamma>0) {

      G4double Edep[100] = {0};
      G4double EdepMax[100] = {0};
      G4int    firstHit[100] = {0};

      G4int detMax = 0;
      
      for(int i=0; i<Ngamma; i++) {
	G4int    det = (*gammaCollection)[i]->GetDetID()-1;
	G4double E   = (*gammaCollection)[i]->GetEdep()/keV;

	if(E>EdepMax[det]) { 
	  EdepMax[det]  = E;
	  firstHit[det] = i;
	}

	Edep[det] += E;

	if(det > detMax)
	  detMax = det;

      }

      //      G4cout << "**** Track Total Energy = " << (*gammaCollection)[0]->GetTotalEnergy()/keV << G4endl;

      //      G4cout << "**** Energy Deposited = " << Edep << G4endl;

      for(int det=0; det<detMax+1; det++){

	if(Edep[det] > 0) {
	  G4int photopeak = 0;
	  
	  if(abs(eventInfo->GetEmittedGammaEnergy(0) - Edep[det])<0.001){
	    photopeak = 1;
	    eventInfo->SetFullEnergy(1);
	  } else {
	    eventInfo->SetFullEnergy(0);
	  }

	  evfile
	    << std::setw(15) << std::right
	    << event_id
	    << std::setw(5) << std::right
	    << (*gammaCollection)[firstHit[det]]->GetDetID()
	    << std::fixed << std::setprecision(2) << std::setw(10) << std::right
	    << Edep[det]
	    << std::setw(10) << std::right
	    << (*gammaCollection)[firstHit[det]]->GetPos().getX()/mm
	    << std::setw(10) << std::right
	    << (*gammaCollection)[firstHit[det]]->GetPos().getY()/mm
	    << std::setw(10) << std::right
	    << (*gammaCollection)[firstHit[det]]->GetPos().getZ()/mm
	    << std::setw(10) << std::right
	    << photopeak
	    << G4endl;
	}
	
      }
      
    }

  }

  G4cout.flags( f );
  
}
// --------------------------------------------------
void EventAction::openEvfile()
{
  if (!evfile.is_open()) evfile.open(outFileName.c_str());
  if (!evfile.is_open())
    G4cout<< "ERROR opening evfile." << G4endl;
  else
    G4cout << "\nOpened output file: " << outFileName << G4endl;
  return;
}
//--------------------------------------------------- 
void EventAction::closeEvfile()
{
	evfile.close();
	return;
}
//----------------------------------------------------
void EventAction::SetOutFile(G4String name)
{
	outFileName = name;
	closeEvfile();
	openEvfile();
	return;
}
