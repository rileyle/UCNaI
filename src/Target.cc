#include "Target.hh"

Target::Target(G4LogicalVolume* experimentalHall_log,
	       Materials* mat)
{
  materials=mat;
  expHall_log=experimentalHall_log;

  Al = materials->FindMaterial("Al");

  Length=2.54*2*cm;
  Radius=2.54*0.25*cm;
  
  Pos.setX(0);
  Pos.setY(0);
  Pos.setZ(0);

  Rot = G4RotationMatrix::IDENTITY;
  Rot.rotateX(90.*deg);

  geoFileName = "";
}


Target::~Target()
{
}

void Target::Construct()
{

  target = new G4Tubs("Target", 0, Radius, Length/2.0, 0, 360.*deg);

  target_log = new G4LogicalVolume(target, Al, "target_log", 0, 0, 0);

  PlaceTarget();

  G4Colour dGrey (0.8, 0.8, 0.8, 1.0);
  G4VisAttributes* Vis = new G4VisAttributes(dGrey);
  Vis->SetVisibility(true);
  Vis->SetForceSolid(true);

  target_log->SetVisAttributes(Vis);
 
  return;
}
//---------------------------------------------------------------------
void Target::PlaceTarget()
{

  // If there is a Target geometry file, use it for placement;
  // if not, use the current Pos and Rot to place a single Target.
  if(geoFileName != ""){
    geoFile.open(geoFileName.c_str());
    if (!geoFile.is_open())
      G4cout<< "ERROR opening Target geometry file." << G4endl;
    else
      G4cout << "\nPositioning Targets using the geometry file: " << geoFileName << G4endl;
    
    char Label[50];
    G4int targetID = 0;
    G4double x, y, z, ax, ay, az;
    while(geoFile >> x >> y >> z >> ax >> ay >> az){
      sprintf(Label, "Target%d", targetID);
      Pos.setX(x);
      Pos.setY(y);
      Pos.setZ(z);
      Rot = G4RotationMatrix::IDENTITY;
      Rot.rotateX(ax*deg);
      Rot.rotateY(ay*deg);
      Rot.rotateZ(az*deg);

      new G4PVPlacement(G4Transform3D(Rot,Pos),
			target_log, G4String(Label), expHall_log,
			false, 0);
      targetID++;
    }
  } else {
    new G4PVPlacement(G4Transform3D(Rot,Pos),
		      target_log, "Target", expHall_log,
		      false, 0); 
  }
}
//---------------------------------------------------------------------
void Target::setX(G4double x)
{
  Pos.setX(x);
}
//---------------------------------------------------------------------
void Target::setY(G4double y)
{
  Pos.setY(y);
}
//---------------------------------------------------------------------
void Target::setZ(G4double z)
{
  Pos.setZ(z);
}
//---------------------------------------------------------------------
void Target::rotateX(G4double ax)
{
  Rot.rotateX(ax);
}
//---------------------------------------------------------------------
void Target::rotateY(G4double ay)
{
  Rot.rotateY(ay);
}
//---------------------------------------------------------------------
void Target::rotateZ(G4double az)
{
  Rot.rotateZ(az);
}
//---------------------------------------------------------------------
