#include "Lead_Brick.hh"

Lead_Brick::Lead_Brick(G4LogicalVolume* experimentalHall_log,
		       Materials* mat)
{
  materials=mat;
  expHall_log=experimentalHall_log;

  Pb = materials->FindMaterial("Pb");

  Length=2.54*6*cm;
  Width=2.54*4*cm;
  Depth=2.54*2*cm;
  
  Pos.setX(0);
  Pos.setY(0);
  Pos.setZ(0);

  Rot = G4RotationMatrix::IDENTITY;

  isPlaced = 0;
}


Lead_Brick::~Lead_Brick()
{
}

G4VPhysicalVolume* Lead_Brick::Construct()
{

  brick = new G4Box("Brick", Width/2.0, Depth/2.0, Length/2.0);

  brick_log = new G4LogicalVolume(brick,Pb,"brick_log",0,0,0);

  PlaceBrick();

  G4Colour dGrey (0.8, 0.8, 0.8, 1.0);
  G4VisAttributes* Vis = new G4VisAttributes(dGrey);
  Vis->SetVisibility(true);
  Vis->SetForceSolid(true);

  brick_log->SetVisAttributes(Vis);
 
  return brick_phys;
}
//---------------------------------------------------------------------
void Lead_Brick::PlaceBrick()
{
   brick_phys = new G4PVPlacement(G4Transform3D(Rot,Pos),
				 brick_log,"Brick",expHall_log,false,0); 
   isPlaced = 1;
}
//---------------------------------------------------------------------
void Lead_Brick::setX(G4double x)
{
  Pos.setX(x);
  if(isPlaced == 1)
    brick_phys->SetTranslation(Pos);
}
//---------------------------------------------------------------------
void Lead_Brick::setY(G4double y)
{
  Pos.setY(y);
  if(isPlaced == 1)
    brick_phys->SetTranslation(Pos);
}
//---------------------------------------------------------------------
void Lead_Brick::setZ(G4double z)
{
  Pos.setZ(z);
  if(isPlaced == 1)
    brick_phys->SetTranslation(Pos);
}
//---------------------------------------------------------------------
void Lead_Brick::rotateX(G4double ax)
{
  Rot.rotateX(ax);
  if(isPlaced == 1)
    brick_phys->SetRotation(&Rot);
}
//---------------------------------------------------------------------
void Lead_Brick::rotateY(G4double ay)
{
  Rot.rotateY(ay);
  if(isPlaced == 1)
    brick_phys->SetRotation(&Rot);
}
//---------------------------------------------------------------------
void Lead_Brick::rotateZ(G4double az)
{
  Rot.rotateZ(az);
  if(isPlaced == 1)
    brick_phys->SetRotation(&Rot);
}
//---------------------------------------------------------------------
