#ifndef TrackerGammaSD_Messenger_h
#define TrackerGammaSD_Messenger_h 1

#include "TrackerGammaSD.hh"
#include "globals.hh"
#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithAnInteger.hh"


class TrackerGammaSD_Messenger: public G4UImessenger
{

  public:
    TrackerGammaSD_Messenger(TrackerGammaSD*);
   ~TrackerGammaSD_Messenger();
    
    void SetNewValue(G4UIcommand*, G4String);
    
  private:
    TrackerGammaSD* tracker;    
    G4UIdirectory*             PrtGDir;
    G4UIcmdWithoutParameter*   PrtGSCmd;
    G4UIcmdWithoutParameter*   PrtGUCmd;

};


#endif

