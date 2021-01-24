#ifndef Source_Capsule_Messenger_h
#define Source_Capsule_Messenger_h 1

#include "Source_Capsule.hh"
#include "globals.hh"
#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithoutParameter.hh"

class Source_Capsule_Messenger: public G4UImessenger
{
  public:
    Source_Capsule_Messenger(Source_Capsule*);
   ~Source_Capsule_Messenger();
    
    void SetNewValue(G4UIcommand*, G4String);
    
  private:
    Source_Capsule* capsule;
   
    G4UIdirectory*             Source_CapsuleDir;  

    G4UIcmdWithADoubleAndUnit* rXCmd;
    G4UIcmdWithADoubleAndUnit* rYCmd;
    G4UIcmdWithADoubleAndUnit* rZCmd;
};


#endif

