#ifndef NaI_Array_H
#define NaI_Array_H 1

#include "NaI_2x2_Detector.hh"
#include "NaI_3x3_Detector.hh"
#include "TrackerGammaSD.hh"

class NaI_Array 
{
public:
  
  NaI_Array(G4LogicalVolume*, Materials*);
  ~NaI_Array();

  // Used by the NaI_Array_Messenger for placing a single detector
  // (when a geometry file is not specified).
  void setX(G4double x){assemblyPos.setX(x);}
  void setY(G4double y){assemblyPos.setY(y);}
  void setZ(G4double z){assemblyPos.setZ(z);}
  void rotateX(G4double ax){assemblyRot.rotateX(ax);}
  void rotateY(G4double ay){assemblyRot.rotateY(ay);}
  void rotateZ(G4double az){assemblyRot.rotateZ(az);}
  void setType(G4String t){detectorType = t;}
  
  void setGeoFile(G4String fname){geoFileName = fname;}

  void Construct();
  
  void MakeSensitive(TrackerGammaSD*);

private:
  G4LogicalVolume *expHall_log;
  Materials *materials;

  NaI_2x2_Detector* detector_2x2;
  NaI_3x3_Detector* detector_3x3;
  
  G4ThreeVector assemblyPos;
  G4RotationMatrix assemblyRot;
  G4String detectorType;
  
  G4String geoFileName;
  std::ifstream geoFile;

};

#endif

