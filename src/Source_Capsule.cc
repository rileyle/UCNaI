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

  thetab = 0.*deg;
  phib = 0.*deg;

  isPlaced = 0;

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

  Rot=G4RotationMatrix::IDENTITY;
 
  Rot.rotateX(0.0*deg);
  Rot.rotateY(thetab);
  Rot.rotateZ(phib);

  capsule_phys = new G4PVPlacement(G4Transform3D(Rot,Pos),
				 capsule_log,"Capsule",expHall_log,false,0); 

  isPlaced = 1;
}
//---------------------------------------------------------------------
void Source_Capsule::setX(G4double x)
{
  Pos.setX(x);
  if(isPlaced)
    capsule_phys->SetTranslation(Pos);
}
//---------------------------------------------------------------------
void Source_Capsule::setY(G4double y)
{
  Pos.setY(y);
  if(isPlaced)
    capsule_phys->SetTranslation(Pos);
}
//---------------------------------------------------------------------
void Source_Capsule::setZ(G4double z)
{
  Pos.setZ(z);
  if(isPlaced)
    capsule_phys->SetTranslation(Pos);
}
//---------------------------------------------------------------------
