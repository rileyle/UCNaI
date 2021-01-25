#include "RunAction.hh"

#include "G4Timer.hh"
extern G4Timer Timer;

RunAction::RunAction(DetectorConstruction* detector, EventAction* ev): myDetector(detector), evaction(ev)
{
  
}


RunAction::~RunAction()
{

}

void RunAction::BeginOfRunAction(const G4Run* run)
{

  G4cout<<" Begining of run "<<G4endl;

  evaction->SetNTotalevents(run->GetNumberOfEventToBeProcessed());
  if(run->GetNumberOfEventToBeProcessed() > 1000000)
    evaction->SetEveryNEvents(10000);
  else if(run->GetNumberOfEventToBeProcessed() > 1000)
    evaction->SetEveryNEvents(1000);
  else if(run->GetNumberOfEventToBeProcessed() > 100)
    evaction->SetEveryNEvents(100);
  else
    evaction->SetEveryNEvents(1);

  G4cout << " Simulating " << run->GetNumberOfEventToBeProcessed()
         << " events." << G4endl;
  
  evaction->openEvfile();

  Timer.Start();

}


 
void RunAction::EndOfRunAction(const G4Run*)
{
  evaction->closeEvfile();

  Timer.Stop();

  G4cout << "                                                     " << G4endl;

  G4double time, hours, minutes, seconds;

  G4cout << "Real time: ";
  time = Timer.GetRealElapsed();
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
    G4cout << std::setprecision(2) << std::setw(5) << seconds;
  G4cout << std::setfill(' ');

  G4cout << "   System time: ";
  time = Timer.GetSystemElapsed();
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
    G4cout << std::setprecision(2) << std::setw(5) << seconds;
  G4cout << std::setfill(' ');

  G4cout << "   User time: ";
  time = Timer.GetUserElapsed();
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
    G4cout << std::setprecision(2) << std::setw(5) << seconds;
  G4cout << std::setfill(' ');

  G4cout << "   "
	 << evaction->GetNTotalevents()/Timer.GetRealElapsed()
	 << " events/s" << G4endl;
}

