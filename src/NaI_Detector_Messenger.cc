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

}



NaI_Detector_Messenger::~NaI_Detector_Messenger()
{
  delete NaIDir;
  delete XCmd;
  delete YCmd;
  delete ZCmd;
}


void NaI_Detector_Messenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  if( command == XCmd )
    {NaIDet->setX(XCmd->GetNewDoubleValue(newValue));}
  if( command == YCmd )
    {NaIDet->setY(YCmd->GetNewDoubleValue(newValue));}
  if( command == ZCmd )
    {NaIDet->setZ(ZCmd->GetNewDoubleValue(newValue));}
}

