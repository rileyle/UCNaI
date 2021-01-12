#include "Source_Capsule_Messenger.hh"

Source_Capsule_Messenger::Source_Capsule_Messenger(Source_Capsule* sc)
:capsule(sc)
{ 
 
  Source_CapsuleDir = new G4UIdirectory("/Source/Capsule/");
  Source_CapsuleDir->SetGuidance("Source_Capsule control.");

  rXCmd = new G4UIcmdWithADoubleAndUnit("/Source/Capsule/rotateX",this);
  rXCmd->SetGuidance("Rotate the brick about the x axis");
  rXCmd->SetParameterName("choice",false);
  rXCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  rYCmd = new G4UIcmdWithADoubleAndUnit("/Source/Capsule/rotateY",this);
  rYCmd->SetGuidance("Rotate the brick about the y axis");
  rYCmd->SetParameterName("choice",false);
  rYCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  rZCmd = new G4UIcmdWithADoubleAndUnit("/Source/Capsule/rotateZ",this);
  rZCmd->SetGuidance("Rotate the brick about the z axis");
  rZCmd->SetParameterName("choice",false);
  rZCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  cCmd = new G4UIcmdWithoutParameter("/Source/Capsule/construct",this);
  cCmd->SetGuidance("Construct the source capsule");
  cCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

}

Source_Capsule_Messenger::~Source_Capsule_Messenger()
{
  delete Source_CapsuleDir;
  delete rXCmd;
  delete rYCmd;
  delete rZCmd;
  delete cCmd;
}


void Source_Capsule_Messenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  if( command == rXCmd )
    {capsule->rotateX(rXCmd->GetNewDoubleValue(newValue));}
  if( command == rYCmd )
    {capsule->rotateY(rYCmd->GetNewDoubleValue(newValue));}
  if( command == rZCmd )
    {capsule->rotateZ(rZCmd->GetNewDoubleValue(newValue));}
  if( command == cCmd )
    {capsule->Construct();}
}

