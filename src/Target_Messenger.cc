#include "Target_Messenger.hh"

Target_Messenger::Target_Messenger(Target* tg)
:target(tg)
{ 
 
  TargetDir = new G4UIdirectory("/Target/");
  TargetDir->SetGuidance("Target control.");

  XCmd = new G4UIcmdWithADoubleAndUnit("/Target/setX",this);
  XCmd->SetGuidance("Set the x position of the brick center");
  XCmd->SetParameterName("choice",false);
  XCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  YCmd = new G4UIcmdWithADoubleAndUnit("/Target/setY",this);
  YCmd->SetGuidance("Set the y position of the brick center");
  YCmd->SetParameterName("choice",false);
  YCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  ZCmd = new G4UIcmdWithADoubleAndUnit("/Target/setZ",this);
  ZCmd->SetGuidance("Set the z position of the brick center");
  ZCmd->SetParameterName("choice",false);
  ZCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  rXCmd = new G4UIcmdWithADoubleAndUnit("/Target/rotateX",this);
  rXCmd->SetGuidance("Rotate the brick about the x axis");
  rXCmd->SetParameterName("choice",false);
  rXCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  rYCmd = new G4UIcmdWithADoubleAndUnit("/Target/rotateY",this);
  rYCmd->SetGuidance("Rotate the brick about the y axis");
  rYCmd->SetParameterName("choice",false);
  rYCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  rZCmd = new G4UIcmdWithADoubleAndUnit("/Target/rotateZ",this);
  rZCmd->SetGuidance("Rotate the brick about the z axis");
  rZCmd->SetParameterName("choice",false);
  rZCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  RCmd = new G4UIcmdWithADoubleAndUnit("/Target/Radius",this);
  RCmd->SetGuidance("Set the radius of the target");
  RCmd->SetParameterName("choice",false);
  RCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  LCmd = new G4UIcmdWithADoubleAndUnit("/Target/Length",this);
  LCmd->SetGuidance("Set the length of the target");
  LCmd->SetParameterName("choice",false);
  LCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  cCmd = new G4UIcmdWithoutParameter("/Target/construct",this);
  cCmd->SetGuidance("Construct the target");
  cCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

}

Target_Messenger::~Target_Messenger()
{
  delete TargetDir;
  delete XCmd;
  delete YCmd;
  delete ZCmd;
  delete rXCmd;
  delete rYCmd;
  delete rZCmd;
  delete RCmd;
  delete LCmd;
  delete cCmd;
}


void Target_Messenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  if( command == XCmd )
    {target->setX(XCmd->GetNewDoubleValue(newValue));}
  if( command == YCmd )
    {target->setY(YCmd->GetNewDoubleValue(newValue));}
  if( command == ZCmd )
    {target->setZ(ZCmd->GetNewDoubleValue(newValue));}
  if( command == rXCmd )
    {target->rotateX(rXCmd->GetNewDoubleValue(newValue));}
  if( command == rYCmd )
    {target->rotateY(rYCmd->GetNewDoubleValue(newValue));}
  if( command == rZCmd )
    {target->rotateZ(rZCmd->GetNewDoubleValue(newValue));}
  if( command == RCmd )
    {target->setR(RCmd->GetNewDoubleValue(newValue));}
  if( command == LCmd )
    {target->setR(LCmd->GetNewDoubleValue(newValue));}
  if( command == cCmd )
    {target->Construct();}
}

