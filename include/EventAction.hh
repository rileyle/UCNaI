#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "TrackerGammaSD.hh"
#include "G4Event.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4ios.hh"
#include "globals.hh"
#include "G4UnitsTable.hh"
#include <fstream>
#include <string>

class EventAction : public G4UserEventAction
{
public:
  EventAction();
  ~EventAction();

  void BeginOfEventAction(const G4Event*);
  void EndOfEventAction(const G4Event*);
  void SetOutFile(G4String); 
  void closeEvfile();
  void openEvfile();

  void SetNTotalevents(G4int n){NTotalEvents = n;}
  G4int GetNTotalevents(){return NTotalEvents;}
  void SetEveryNEvents(G4int n){everyNevents = n;}
  G4int GetEveryNEvents(){return everyNevents;}

private:
  G4int gammaCollectionID;
  G4String outFileName;
  std::ofstream evfile;
  G4int NTotalEvents;
  G4int everyNevents;
  G4int timerCount;
  G4double eventsPerSecond;

};

#endif //EVENTACTION_H
