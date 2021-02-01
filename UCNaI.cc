//PROGRAM MPP4
#include "G4RunManager.hh"
#include "G4UImanager.hh"

#include "G4UIterminal.hh"
#include "G4UItcsh.hh"

#ifdef G4UI_USE_XM
#include "G4UIXm.hh"
#endif

#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "PrimaryGeneratorAction.hh"
#include "PrimaryGeneratorAction_Messenger.hh"
#include "EventAction.hh"
#include "EventAction_Messenger.hh"
#include "TrackingAction.hh"
#include "RunAction.hh"

#ifdef G4VIS_USE
#include "VisManager.hh"
#endif

#include "G4Timer.hh"
G4Timer Timer;
G4Timer Timerintern;

int main(int argc,char** argv) 
{
  // Construct the default run manager
  G4RunManager* runManager = new G4RunManager;

  // set mandatory initialization classes
  DetectorConstruction* detector=new DetectorConstruction();
  //  PhysicsList *physicsList = new PhysicsList(detector);
  PhysicsList *physicsList = new PhysicsList();
  runManager->SetUserInitialization(detector);
  runManager->SetUserInitialization(physicsList);

  // set mandatory user action class
  EventAction* eventAction = new EventAction();
  EventAction_Messenger* eventActionMessenger;
  eventActionMessenger = new EventAction_Messenger(eventAction);
  runManager->SetUserAction(eventAction);
  PrimaryGeneratorAction* generatorAction= new PrimaryGeneratorAction(detector);
  PrimaryGeneratorAction_Messenger* generatorActionMessenger;
  generatorActionMessenger=new PrimaryGeneratorAction_Messenger(generatorAction);
  runManager->SetUserAction(generatorAction);
  RunAction* runAction = new RunAction(detector,eventAction);
  runManager->SetUserAction(runAction);

  TrackingAction* trackingAction = new TrackingAction(eventAction);
  runManager->SetUserAction(trackingAction);

  G4UIsession* session=0;

#ifdef G4VIS_USE
  // visualization manager
  G4VisManager* visManager=0;
#endif

  if (argc==1)   // Define UI session for interactive mode.
    {

#ifdef G4VIS_USE
      // visualization manager
      visManager = new VisManager; 
      visManager->Initialize();
#endif

// G4UIterminal is a (dumb) terminal.
#ifdef G4UI_USE_TCSH
      session = new G4UIterminal(new G4UItcsh);      
#else
      session = new G4UIterminal();
#endif

    }

  // Initialize G4 kernel
  //  runManager->Initialize();
  // Actually, we don't, so that we can set parameters before
  // the detector is constructed.

  
  // get the pointer to the UI manager and set verbosities
  G4UImanager* UI = G4UImanager::GetUIpointer();

  if (session)   // Define UI session for interactive mode.
    {
      session->SessionStart();
      delete session;
    }
  else           // Batch mode
    { 
      G4String command = "/control/execute ";
      G4String fileName = argv[1];
      UI->ApplyCommand(command+fileName);
    }

  // job termination
  if(argc==1){
#ifdef G4VIS_USE
  delete visManager;
#endif
  }

  delete runManager;

  return 0;
}
