#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "DetectorConstruction.hh"
#include "G4Run.hh"
#include "globals.hh"
#include "G4UnitsTable.hh"
#include "EventAction.hh"

class RunAction : public G4UserRunAction
{
  public:
    RunAction(DetectorConstruction*,EventAction*);
   ~RunAction();

  public:
    void BeginOfRunAction(const G4Run*);
    void EndOfRunAction(const G4Run*);

  private:
  DetectorConstruction* myDetector;
  EventAction* evaction;

};




#endif

    
