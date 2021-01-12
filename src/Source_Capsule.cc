#include "Source_Capsule.hh"

Source_Capsule::Source_Capsule(G4LogicalVolume* experimentalHall_log,
		       Materials* mat)
{
  materials=mat;
  expHall_log=experimentalHall_log;

  polyethylene = materials->FindMaterial("G4_POLYETHYLENE");

  Depth=2.54*.1875*cm;
  Radius=2.54*.5*cm;
  innerRadius=2.54*.125*cm;
  startAngle      = 45.*deg;
  spanningAngle   = 360.*deg;

  Pos.setX(0);
  Pos.setY(0);
  Pos.setZ(0);

  Rot = G4RotationMatrix::IDENTITY;
  
}

Source_Capsule::~Source_Capsule()
{
}

G4VPhysicalVolume* Source_Capsule::Construct()
{

  capsule = new G4Tubs("Capsule",innerRadius,Radius,Depth/2.0,startAngle,spanningAngle);

  capsule_log = new G4LogicalVolume(capsule,polyethylene,"capsule_log",0,0,0);

  PlaceCapsule();

  G4Colour dGrey (0.8, 0.8, 0.8, 1.0);
  G4VisAttributes* Vis = new G4VisAttributes(dGrey);
  Vis->SetVisibility(true);
  Vis->SetForceSolid(true);

  capsule_log->SetVisAttributes(Vis);

  return capsule_phys;
}
//---------------------------------------------------------------------
void Source_Capsule::PlaceCapsule()
{

  capsule_phys = new G4PVPlacement(G4Transform3D(Rot,Pos),
				   capsule_log, "Capsule",
				   expHall_log, false, 0); 

}
//---------------------------------------------------------------------
void Source_Capsule::setX(G4double x)
{
  Pos.setX(x);
}
//---------------------------------------------------------------------
void Source_Capsule::setY(G4double y)
{
  Pos.setY(y);
}
//---------------------------------------------------------------------
void Source_Capsule::setZ(G4double z)
{
  Pos.setZ(z);
}
//---------------------------------------------------------------------
void Source_Capsule::rotateX(G4double ax)
{
  Rot.rotateX(ax);
}
//---------------------------------------------------------------------
void Source_Capsule::rotateY(G4double ay)
{
  Rot.rotateY(ay);
}
//---------------------------------------------------------------------
void Source_Capsule::rotateZ(G4double az)
{
  Rot.rotateZ(az);
}
//---------------------------------------------------------------------
