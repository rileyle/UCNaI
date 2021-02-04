#include "Lead_Brick_Messenger.hh"

Lead_Brick_Messenger::Lead_Brick_Messenger(Lead_Brick* LB)
:Brick(LB)
{ 
 
  BrickDir = new G4UIdirectory("/Brick/");
  BrickDir->SetGuidance("Brick control.");

  XCmd = new G4UIcmdWithADoubleAndUnit("/Brick/setX",this);
  XCmd->SetGuidance("Set the x position of the brick center");
  XCmd->SetParameterName("choice",false);
  XCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  YCmd = new G4UIcmdWithADoubleAndUnit("/Brick/setY",this);
  YCmd->SetGuidance("Set the y position of the brick center");
  YCmd->SetParameterName("choice",false);
  YCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  ZCmd = new G4UIcmdWithADoubleAndUnit("/Brick/setZ",this);
  ZCmd->SetGuidance("Set the z position of the brick center");
  ZCmd->SetParameterName("choice",false);
  ZCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  rXCmd = new G4UIcmdWithADoubleAndUnit("/Brick/rotateX",this);
  rXCmd->SetGuidance("Rotate the brick about the x axis");
  rXCmd->SetParameterName("choice",false);
  rXCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  rYCmd = new G4UIcmdWithADoubleAndUnit("/Brick/rotateY",this);
  rYCmd->SetGuidance("Rotate the brick about the y axis");
  rYCmd->SetParameterName("choice",false);
  rYCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  rZCmd = new G4UIcmdWithADoubleAndUnit("/Brick/rotateZ",this);
  rZCmd->SetGuidance("Rotate the brick about the z axis");
  rZCmd->SetParameterName("choice",false);
  rZCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  cCmd = new G4UIcmdWithoutParameter("/Brick/Construct",this);
  cCmd->SetGuidance("Construct the brick");
  cCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  GCmd = new G4UIcmdWithAString("/Brick/GeometryFile",this);
  GCmd->SetGuidance("Set the brick geometry file name.");
  GCmd->SetParameterName("choice",false);
  GCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

}

Lead_Brick_Messenger::~Lead_Brick_Messenger()
{
  delete BrickDir;
  delete XCmd;
  delete YCmd;
  delete ZCmd;
  delete rXCmd;
  delete rYCmd;
  delete rZCmd;
  delete cCmd;
  delete GCmd;
}


void Lead_Brick_Messenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  if( command == XCmd )
    {Brick->setX(XCmd->GetNewDoubleValue(newValue));}
  if( command == YCmd )
    {Brick->setY(YCmd->GetNewDoubleValue(newValue));}
  if( command == ZCmd )
    {Brick->setZ(ZCmd->GetNewDoubleValue(newValue));}
  if( command == rXCmd )
    {Brick->rotateX(rXCmd->GetNewDoubleValue(newValue));}
  if( command == rYCmd )
    {Brick->rotateY(rYCmd->GetNewDoubleValue(newValue));}
  if( command == rZCmd )
    {Brick->rotateZ(rZCmd->GetNewDoubleValue(newValue));}
  if( command == cCmd )
    {Brick->Construct();}
  if( command == GCmd )
    {Brick->setGeoFile(newValue);}
}

