#include "Experimental_Hall_Messenger.hh"


Experimental_Hall_Messenger::Experimental_Hall_Messenger(Experimental_Hall* EH)
:ExpHall(EH)
{ 
 
  ExpHallDir = new G4UIdirectory("/ExpHall/");
  ExpHallDir->SetGuidance("Exp. Hall control.");
  
  MatCmd = new G4UIcmdWithAString("/ExpHall/Material",this);
  MatCmd->SetGuidance("Select material for the exp. hall.");
  MatCmd->SetParameterName("choice",false);
  MatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  XCmd = new G4UIcmdWithADoubleAndUnit("/ExpHall/X_length",this);
  XCmd->SetGuidance("Select the X length for the exp. hall");
  XCmd->SetParameterName("choice",false);
  XCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  YCmd = new G4UIcmdWithADoubleAndUnit("/ExpHall/Y_length",this);
  YCmd->SetGuidance("Select the Y length for the exp. hall");
  YCmd->SetParameterName("choice",false);
  YCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  ZCmd = new G4UIcmdWithADoubleAndUnit("/ExpHall/Z_length",this);
  ZCmd->SetGuidance("Select the Z length for the exp. hall");
  ZCmd->SetParameterName("choice",false);
  ZCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  

  RepCmd = new G4UIcmdWithoutParameter("/ExpHall/Report",this);
  RepCmd->SetGuidance("Report exp. hall parameters");  

}



Experimental_Hall_Messenger::~Experimental_Hall_Messenger()
{
  delete XCmd;
  delete YCmd;
  delete ZCmd;
  delete MatCmd;
  delete ExpHallDir;
  delete RepCmd;
}


void Experimental_Hall_Messenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  if( command == MatCmd )
   { ExpHall->setMaterial(newValue);} 
  if( command == XCmd )
   { ExpHall->setX(XCmd->GetNewDoubleValue(newValue));}
  if( command == YCmd )
   { ExpHall->setY(YCmd->GetNewDoubleValue(newValue));}
  if( command == ZCmd )
   { ExpHall->setZ(ZCmd->GetNewDoubleValue(newValue));}
  if( command == RepCmd )
   { ExpHall->Report();}

}

