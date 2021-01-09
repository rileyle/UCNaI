#include "Experimental_Hall.hh"

Experimental_Hall::Experimental_Hall(Materials* mat)
{
  materials=mat;
  expHall_x = 400.*cm;
  expHall_y = 400.*cm;
  expHall_z = 400.*cm;

  ExperimentalHallMaterial = materials->FindMaterial("G4_Galactic");


}

Experimental_Hall::~Experimental_Hall()
{;}
//-----------------------------------------------------------------------------
G4VPhysicalVolume* Experimental_Hall::Construct()
{

  ExperimentalHall
    = new G4Box("expHall_box",expHall_x,expHall_y,expHall_z);

  ExperimentalHall_log = new G4LogicalVolume(ExperimentalHall,
                                             ExperimentalHallMaterial,"expHall_log",0,0,0);

  ExperimentalHall_phys = new G4PVPlacement(0,G4ThreeVector(),
                                      ExperimentalHall_log,"expHall",0,false,0);

  ExperimentalHall_log-> SetVisAttributes (G4VisAttributes::Invisible);
  
  return ExperimentalHall_phys;
}
//-----------------------------------------------------------------------------
void Experimental_Hall::setX(G4double X)
{
   expHall_x=X/2.;
   ExperimentalHall->SetXHalfLength(expHall_x);
   G4cout<<"----> Exp. Hall X length is set to "<<G4BestUnit(2.*ExperimentalHall->GetXHalfLength(),"Length")<<G4endl;
}
//-----------------------------------------------------------------------------
void Experimental_Hall::setY(G4double Y)
{
   expHall_y=Y/2.;
   ExperimentalHall->SetYHalfLength(expHall_y);
   G4cout<<"----> Exp. Hall Y length is set to "<<G4BestUnit(2.*ExperimentalHall->GetYHalfLength(),"Length")<<G4endl;
}
//-----------------------------------------------------------------------------
void Experimental_Hall::setZ(G4double Z)
{
   expHall_z=Z/2.;
   ExperimentalHall->SetZHalfLength(expHall_z);
   G4cout<<"----> Exp. Hall Z length is set to "<<G4BestUnit(2.*ExperimentalHall->GetZHalfLength(),"Length")<<G4endl;
}

//-----------------------------------------------------------------------------
void Experimental_Hall::Report()
{
     G4cout<<"----> Exp. Hall material set to     "<<ExperimentalHall_log->GetMaterial()->GetName()<< G4endl;   
     G4cout<<"----> Exp. Hall X length is set to "<<G4BestUnit(2.*ExperimentalHall->GetXHalfLength(),"Length")<<G4endl;
     G4cout<<"----> Exp. Hall Y length is set to "<<G4BestUnit(2.*ExperimentalHall->GetYHalfLength(),"Length")<<G4endl;
     G4cout<<"----> Exp. Hall Z length is set to "<<G4BestUnit(2.*ExperimentalHall->GetZHalfLength(),"Length")<<G4endl;
  

}
//---------------------------------------------------------------------
void Experimental_Hall::setMaterial(G4String materialName)
{
  // search the material by its name 
  ExperimentalHallMaterial = materials->FindMaterial(materialName);  
  ExperimentalHall_log->SetMaterial(ExperimentalHallMaterial);
  G4cout<<"----> Exp. Hall material set to     "<<ExperimentalHall_log->GetMaterial()->GetName()<< G4endl;                 
}
