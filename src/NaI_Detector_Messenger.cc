#include "NaI_Detector_Messenger.hh"

NaI_Detector_Messenger::NaI_Detector_Messenger(NaI_Detector* SD)
:NaIDet(SD)
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

  RCmd = new G4UIcmdWithADoubleAndUnit("/NaI/setR",this);
  RCmd->SetGuidance("Set the radius of the NaI crystal");
  RCmd->SetParameterName("choice",false);
  RCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  LCmd = new G4UIcmdWithADoubleAndUnit("/NaI/setL",this);
  LCmd->SetGuidance("Set the length of the NaI crystal");
  LCmd->SetParameterName("choice",false);
  LCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

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

  GCmd = new G4UIcmdWithAString("/NaI/GeometryFile",this);
  GCmd->SetGuidance("Set the geometry file name.");
  GCmd->SetParameterName("choice",false);
  GCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

}



NaI_Detector_Messenger::~NaI_Detector_Messenger()
{
  delete NaIDir;
  delete XCmd;
  delete YCmd;
  delete ZCmd;
  delete RCmd;
  delete LCmd;
  delete rXCmd;
  delete rYCmd;
  delete rZCmd;
  delete GCmd;
}


void NaI_Detector_Messenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  if( command == XCmd )
    {NaIDet->setX(XCmd->GetNewDoubleValue(newValue));}
  if( command == YCmd )
    {NaIDet->setY(YCmd->GetNewDoubleValue(newValue));}
  if( command == ZCmd )
    {NaIDet->setZ(ZCmd->GetNewDoubleValue(newValue));}
  if( command == RCmd )
    {NaIDet->setR(RCmd->GetNewDoubleValue(newValue));}
  if( command == LCmd )
    {NaIDet->setL(LCmd->GetNewDoubleValue(newValue));}
  if( command == ZCmd )
    {NaIDet->setZ(ZCmd->GetNewDoubleValue(newValue));}
  if( command == rXCmd )
    {NaIDet->rotateX(rXCmd->GetNewDoubleValue(newValue));}
  if( command == rYCmd )
    {NaIDet->rotateY(rYCmd->GetNewDoubleValue(newValue));}
  if( command == rZCmd )
    {NaIDet->rotateZ(rZCmd->GetNewDoubleValue(newValue));}
  if( command == GCmd )
    {NaIDet->setGeoFile(newValue);}
}
