#include "EventAction_Messenger.hh"


EventAction_Messenger::EventAction_Messenger(EventAction* EA):theEventAction(EA) 
{ 

  OutputDir = new G4UIdirectory("/Output/");
  OutputDir->SetGuidance("Event by event output control.");

  OutFileCmd = new G4UIcmdWithAString("/Output/Filename",this);
  OutFileCmd->SetGuidance("Output file name.");

}



EventAction_Messenger::~EventAction_Messenger()

{  

  delete OutputDir;
  delete OutFileCmd;

}



void EventAction_Messenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 

  if( command == OutFileCmd )
    {theEventAction->SetOutFile(newValue);}

}

