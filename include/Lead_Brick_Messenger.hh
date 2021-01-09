#ifndef Lead_Brick_Messenger_h
#define Lead_Brick_Messenger_h 1

#include "Lead_Brick.hh"
#include "globals.hh"
#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithoutParameter.hh"

class Lead_Brick_Messenger: public G4UImessenger
{
  public:
    Lead_Brick_Messenger(Lead_Brick*);
   ~Lead_Brick_Messenger();
    
    void SetNewValue(G4UIcommand*, G4String);
    
  private:
    Lead_Brick* Brick;
   
    G4UIdirectory*             BrickDir;  

    G4UIcmdWithADoubleAndUnit* XCmd;
    G4UIcmdWithADoubleAndUnit* YCmd;
    G4UIcmdWithADoubleAndUnit* ZCmd;
    G4UIcmdWithADoubleAndUnit* rXCmd;
    G4UIcmdWithADoubleAndUnit* rYCmd;
    G4UIcmdWithADoubleAndUnit* rZCmd;
    G4UIcmdWithoutParameter*   cCmd;
};


#endif

