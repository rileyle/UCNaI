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
  Pos.setZ(-10*cm);

  Rot = G4RotationMatrix::IDENTITY;
  Rot.rotateX(90.*deg);

  isPlaced = 0;
}


Target::~Target()
{
}

G4VPhysicalVolume* Target::Construct()
{

  target = new G4Tubs("Target", 0, Radius, Length/2.0, 0, 360.*deg);

  target_log = new G4LogicalVolume(target, Al, "target_log", 0, 0, 0);

  PlaceTarget();

  G4Colour dGrey (0.8, 0.8, 0.8, 1.0);
  G4VisAttributes* Vis = new G4VisAttributes(dGrey);
  Vis->SetVisibility(true);
  Vis->SetForceSolid(true);

  target_log->SetVisAttributes(Vis);
 
  return target_phys;
}
//---------------------------------------------------------------------
void Target::PlaceTarget()
{
   target_phys = new G4PVPlacement(G4Transform3D(Rot,Pos),
				   target_log, "Target", expHall_log,
				   false, 0); 
   isPlaced = 1;
}
//---------------------------------------------------------------------
void Target::setX(G4double x)
{
  Pos.setX(x);
  if(isPlaced == 1)
    target_phys->SetTranslation(Pos);
}
//---------------------------------------------------------------------
void Target::setY(G4double y)
{
  Pos.setY(y);
  if(isPlaced == 1)
    target_phys->SetTranslation(Pos);
}
//---------------------------------------------------------------------
void Target::setZ(G4double z)
{
  Pos.setZ(z);
  if(isPlaced == 1)
    target_phys->SetTranslation(Pos);
}
//---------------------------------------------------------------------
void Target::rotateX(G4double ax)
{
  Rot.rotateX(ax);
  if(isPlaced == 1)
    target_phys->SetRotation(&Rot);
}
//---------------------------------------------------------------------
void Target::rotateY(G4double ay)
{
  Rot.rotateY(ay);
  if(isPlaced == 1)
    target_phys->SetRotation(&Rot);
}
//---------------------------------------------------------------------
void Target::rotateZ(G4double az)
{
  Rot.rotateZ(az);
  if(isPlaced == 1)
    target_phys->SetRotation(&Rot);
}
//---------------------------------------------------------------------
