#ifndef Experimental_Hall_Messenger_h
#define Experimental_Hall_Messenger_h 1

#include "Experimental_Hall.hh"
#include "globals.hh"
#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"



class Experimental_Hall_Messenger: public G4UImessenger
{
  public:
    Experimental_Hall_Messenger(Experimental_Hall*);
   ~Experimental_Hall_Messenger();
    
    void SetNewValue(G4UIcommand*, G4String);
    
  private:
    Experimental_Hall* ExpHall;
    
    G4UIdirectory*             ExpHallDir;
    G4UIcmdWithAString*        MatCmd;  
    G4UIcmdWithADoubleAndUnit* XCmd;
    G4UIcmdWithADoubleAndUnit* YCmd;
    G4UIcmdWithADoubleAndUnit* ZCmd;
    G4UIcmdWithoutParameter*   RepCmd;
  

};


#endif

