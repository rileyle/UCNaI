#include "PrimaryGeneratorAction_Messenger.hh"


PrimaryGeneratorAction_Messenger::PrimaryGeneratorAction_Messenger(PrimaryGeneratorAction* pga):PGA(pga) 
{ 
  SrcDir = new G4UIdirectory("/Source/");
  SrcDir->SetGuidance("Select source parameters for simulation.");
  
  SrcCmd  = new G4UIcmdWithAString("/Source/Set",this);
  SrcCmd->SetGuidance("Set source type (eu152 or cs137 or au or simple)");
  SrcCmd->SetParameterName("Source type",false);
  SrcCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  SrcECmd = new G4UIcmdWithADoubleAndUnit("/Source/setEnergy",this);
  SrcECmd->SetGuidance("Set gamma-ray energy for the source");
  SrcECmd->SetParameterName("Source Energy",false);
  SrcECmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  SrcXCmd = new G4UIcmdWithADoubleAndUnit("/Source/setX",this);
  SrcXCmd->SetGuidance("Set X position for the source");
  SrcXCmd->SetParameterName("Source X position",false);
  SrcXCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  SrcYCmd = new G4UIcmdWithADoubleAndUnit("/Source/setY",this);
  SrcYCmd->SetGuidance("Set Y position for the source");
  SrcYCmd->SetParameterName("Source Y position",false);
  SrcYCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  SrcZCmd = new G4UIcmdWithADoubleAndUnit("/Source/setZ",this);
  SrcZCmd->SetGuidance("Set Z position for the source");
  SrcZCmd->SetParameterName("Source Z position",false);
  SrcZCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  SrcCCmd = new G4UIcmdWithoutParameter("/Source/Capsule",this);
  SrcCCmd->SetGuidance("Construct source capsule");
  
}

PrimaryGeneratorAction_Messenger::~PrimaryGeneratorAction_Messenger()
{  
  delete SrcDir;
  delete SrcCmd;
  delete SrcECmd;
  delete SrcXCmd;
  delete SrcYCmd;
  delete SrcZCmd;
  delete SrcCCmd;
}

void PrimaryGeneratorAction_Messenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 

  if( command == SrcCmd )
    {PGA ->SetSourceType(newValue);}

  if( command == SrcECmd )
    {PGA ->SetSourceEnergy(SrcECmd->GetNewDoubleValue(newValue));}

  if( command == SrcXCmd )
    {PGA ->SetSourceX(SrcXCmd->GetNewDoubleValue(newValue));}

  if( command == SrcYCmd )
    {PGA ->SetSourceY(SrcYCmd->GetNewDoubleValue(newValue));}

  if( command == SrcZCmd )
    {PGA ->SetSourceZ(SrcZCmd->GetNewDoubleValue(newValue));}

  if( command == SrcCCmd )
    {PGA ->getDetectorConstruction()->getSourceCapsule()->Construct();}

}

