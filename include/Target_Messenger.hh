#ifndef Target_Messenger_h
#define Target_Messenger_h 1

#include "Target.hh"
#include "globals.hh"
#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithoutParameter.hh"

class Target_Messenger: public G4UImessenger
{
  public:
    Target_Messenger(Target*);
   ~Target_Messenger();
    
    void SetNewValue(G4UIcommand*, G4String);
    
  private:
    Target* target;
   
    G4UIdirectory*             TargetDir;  

    G4UIcmdWithADoubleAndUnit* XCmd;
    G4UIcmdWithADoubleAndUnit* YCmd;
    G4UIcmdWithADoubleAndUnit* ZCmd;
    G4UIcmdWithADoubleAndUnit* rXCmd;
    G4UIcmdWithADoubleAndUnit* rYCmd;
    G4UIcmdWithADoubleAndUnit* rZCmd;
    G4UIcmdWithADoubleAndUnit* RCmd;
    G4UIcmdWithADoubleAndUnit* LCmd;
    G4UIcmdWithoutParameter*   cCmd;
    G4UIcmdWithAString*        GCmd;
};


#endif

