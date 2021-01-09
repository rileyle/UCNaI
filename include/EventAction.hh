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
//#include "Results.hh"
class EventAction : public G4UserEventAction
{
  public:
    EventAction();      //LR EventAction(Results*);
   ~EventAction();

    void BeginOfEventAction(const G4Event*);
    void EndOfEventAction(const G4Event*);
	void SetOutFile(G4String);  // TB
    //void SetOutFile(G4String name) {    TB
    //  outFileName = name;
    //};
	void closeEvfile();
	void openEvfile();
  private:
  //LR Results* results;
  G4int gammaCollectionID;
  G4String outFileName;
  std::ofstream evfile;
};

#endif //EVENTACTION_H
