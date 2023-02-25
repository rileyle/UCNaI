#ifndef PrimaryGeneratorAction_Messenger_h
#define PrimaryGeneratorAction_Messenger_h 1

#include "PrimaryGeneratorAction.hh"
#include "globals.hh"
#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithAnInteger.hh"


class PrimaryGeneratorAction_Messenger: public G4UImessenger
{
public:
  PrimaryGeneratorAction_Messenger(PrimaryGeneratorAction*);
  ~PrimaryGeneratorAction_Messenger();
    
  void SetNewValue(G4UIcommand*, G4String);
    
private:
  PrimaryGeneratorAction*      PGA;    
  G4UIdirectory*               SrcDir;
  G4UIcmdWithADoubleAndUnit*   SrcECmd;
  G4UIcmdWithADoubleAndUnit*   SrcMCmd;
  G4UIcmdWithADoubleAndUnit*   SrcXCmd;
  G4UIcmdWithADoubleAndUnit*   SrcYCmd;
  G4UIcmdWithADoubleAndUnit*   SrcZCmd;
  G4UIcmdWithoutParameter*     SrcCCmd;

};


#endif

