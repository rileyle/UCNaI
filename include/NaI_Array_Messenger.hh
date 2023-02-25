#ifndef NaI_Array_Messenger_h
#define NaI_Array_Messenger_h 1

#include "NaI_Array.hh"
#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithoutParameter.hh"

class NaI_Array_Messenger: public G4UImessenger
{
  public:
    NaI_Array_Messenger(NaI_Array*);
   ~NaI_Array_Messenger();
    
    void SetNewValue(G4UIcommand*, G4String);
    
  private:
    NaI_Array* NaIArray;
   
    G4UIdirectory*             NaIDir;  

    G4UIcmdWithADoubleAndUnit* XCmd;
    G4UIcmdWithADoubleAndUnit* YCmd;
    G4UIcmdWithADoubleAndUnit* ZCmd;
    G4UIcmdWithADoubleAndUnit* rXCmd;
    G4UIcmdWithADoubleAndUnit* rYCmd;
    G4UIcmdWithADoubleAndUnit* rZCmd;
    G4UIcmdWithAString* TCmd;
    G4UIcmdWithAString* GCmd;
};


#endif

