#include "NaI_Array_Messenger.hh"

NaI_Array_Messenger::NaI_Array_Messenger(NaI_Array* NA)
:NaIArray(NA)
{ 
 
  NaIDir = new G4UIdirectory("/NaI/");
  NaIDir->SetGuidance("NaI control.");

  XCmd = new G4UIcmdWithADoubleAndUnit("/NaI/setX",this);
  XCmd->SetGuidance("Set the x position of the detector (crystal center)");
  XCmd->SetParameterName("choice",false);
  XCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  YCmd = new G4UIcmdWithADoubleAndUnit("/NaI/setY",this);
  YCmd->SetGuidance("Set the y position of the detector (crystal center)");
  YCmd->SetParameterName("choice",false);
  YCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  ZCmd = new G4UIcmdWithADoubleAndUnit("/NaI/setZ",this);
  ZCmd->SetGuidance("Set the z position of the detector (crystal center)");
  ZCmd->SetParameterName("choice",false);
  ZCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  rXCmd = new G4UIcmdWithADoubleAndUnit("/NaI/rotateX",this);
  rXCmd->SetGuidance("Rotate the detector about the x axis");
  rXCmd->SetParameterName("choice",false);
  rXCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  rYCmd = new G4UIcmdWithADoubleAndUnit("/NaI/rotateY",this);
  rYCmd->SetGuidance("Rotate the detector about the y axis");
  rYCmd->SetParameterName("choice",false);
  rYCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  rZCmd = new G4UIcmdWithADoubleAndUnit("/NaI/rotateZ",this);
  rZCmd->SetGuidance("Rotate the detector about the z axis");
  rZCmd->SetParameterName("choice",false);
  rZCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  TCmd = new G4UIcmdWithAString("/NaI/Type",this);
  TCmd->SetGuidance("Detector type (2x2 or 3x3)");
  TCmd->SetParameterName("choice",false);
  TCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  GCmd = new G4UIcmdWithAString("/NaI/GeometryFile",this);
  GCmd->SetGuidance("Set the geometry file name.");
  GCmd->SetParameterName("choice",false);
  GCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

}



NaI_Array_Messenger::~NaI_Array_Messenger()
{
  delete NaIDir;
  delete XCmd;
  delete YCmd;
  delete ZCmd;
  delete rXCmd;
  delete rYCmd;
  delete rZCmd;
  delete TCmd;
  delete GCmd;
}


void NaI_Array_Messenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  if( command == XCmd )
    {NaIArray->setX(XCmd->GetNewDoubleValue(newValue));}
  if( command == YCmd )
    {NaIArray->setY(YCmd->GetNewDoubleValue(newValue));}
  if( command == ZCmd )
    {NaIArray->setZ(ZCmd->GetNewDoubleValue(newValue));}
  if( command == ZCmd )
    {NaIArray->setZ(ZCmd->GetNewDoubleValue(newValue));}
  if( command == rXCmd )
    {NaIArray->rotateX(rXCmd->GetNewDoubleValue(newValue));}
  if( command == rYCmd )
    {NaIArray->rotateY(rYCmd->GetNewDoubleValue(newValue));}
  if( command == rZCmd )
    {NaIArray->rotateZ(rZCmd->GetNewDoubleValue(newValue));}
  if( command == TCmd )
    {NaIArray->setType(newValue);}
  if( command == GCmd )
    {NaIArray->setGeoFile(newValue);}
}