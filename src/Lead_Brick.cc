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

  geoFileName = "";
}


Lead_Brick::~Lead_Brick()
{
}

void Lead_Brick::Construct()
{

  brick = new G4Box("Brick", Width/2.0, Depth/2.0, Length/2.0);

  brick_log = new G4LogicalVolume(brick,Pb,"brick_log",0,0,0);

  PlaceBrick();

  G4Colour dGrey (0.8, 0.8, 0.8, 1.0);
  G4VisAttributes* Vis = new G4VisAttributes(dGrey);
  Vis->SetVisibility(true);
  Vis->SetForceSolid(true);

  brick_log->SetVisAttributes(Vis);
 
  return;
}
//---------------------------------------------------------------------
void Lead_Brick::PlaceBrick()
{
    // If there is a Target geometry file, use it for placement;
  // if not, use the current Pos and Rot to place a single Target.
  if(geoFileName != ""){
    geoFile.open(geoFileName.c_str());
    if (!geoFile.is_open())
      G4cout<< "ERROR opening Brick geometry file." << G4endl;
    else
      G4cout << "\nPositioning Bricks using the geometry file: " << geoFileName << G4endl;
    
    char Label[50];
    G4int brickID = 0;
    G4double x, y, z, ax, ay, az;
    while(geoFile >> x >> y >> z >> ax >> ay >> az){
      sprintf(Label, "Brick%d", brickID);
      Pos.setX(x);
      Pos.setY(y);
      Pos.setZ(z);
      Rot = G4RotationMatrix::IDENTITY;
      Rot.rotateX(ax*deg);
      Rot.rotateY(ay*deg);
      Rot.rotateZ(az*deg);

      new G4PVPlacement(G4Transform3D(Rot,Pos),
			brick_log, G4String(Label), expHall_log,
			false,0 ); 

      brickID++;
    }
  } else {
    new G4PVPlacement(G4Transform3D(Rot,Pos),
		      brick_log,"Brick",expHall_log,false,0); 
  }
}
//---------------------------------------------------------------------
void Lead_Brick::setX(G4double x)
{
  Pos.setX(x);
}
//---------------------------------------------------------------------
void Lead_Brick::setY(G4double y)
{
  Pos.setY(y);
}
//---------------------------------------------------------------------
void Lead_Brick::setZ(G4double z)
{
  Pos.setZ(z);
}
//---------------------------------------------------------------------
void Lead_Brick::rotateX(G4double ax)
{
  Rot.rotateX(ax);
}
//---------------------------------------------------------------------
void Lead_Brick::rotateY(G4double ay)
{
  Rot.rotateY(ay);
}
//---------------------------------------------------------------------
void Lead_Brick::rotateZ(G4double az)
{
  Rot.rotateZ(az);
}
//---------------------------------------------------------------------
