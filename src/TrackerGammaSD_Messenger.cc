#include "TrackerGammaSD_Messenger.hh"


TrackerGammaSD_Messenger::TrackerGammaSD_Messenger(TrackerGammaSD* TGSD)
:tracker(TGSD) 
{ 

  PrtGDir = new G4UIdirectory("/GammaPrint/");
  PrtGDir->SetGuidance("Event by event print control for.");

  PrtGSCmd = new G4UIcmdWithoutParameter("/GammaPrint/Track_Set",this);
  PrtGSCmd->SetGuidance("Sets printing of track gamma results.");

  PrtGUCmd = new G4UIcmdWithoutParameter("/GammaPrint/Track_UnSet",this);
  PrtGUCmd->SetGuidance("Un sets printing of track gamma results.");
  
}



TrackerGammaSD_Messenger::~TrackerGammaSD_Messenger()

{  

  delete PrtGDir;
  delete PrtGSCmd;
  delete PrtGUCmd;

}



void TrackerGammaSD_Messenger::SetNewValue(G4UIcommand* command,G4String)
{ 

  if( command == PrtGSCmd )
    {tracker ->SetPrint();}

  if( command == PrtGUCmd )
    {tracker ->UnSetPrint();}

}

