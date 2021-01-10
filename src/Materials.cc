#include "Materials.hh"

 Materials:: Materials()
{
  // Elements
 
  elementH  = new G4Element("Hydrogen",  "H",  1.,  1.0079*g/mole);
  elementC  = new G4Element("Carbon",    "C",  6.,  12.011*g/mole);
  elementN  = new G4Element("Nitrogen",  "N",  7.,  14.007*g/mole);
  elementO  = new G4Element("Oxygen",    "O",  8., 15.9994*g/mole);
  elementMg = new G4Element("Magnesium", "Mg",12., 24.3050*g/mole);
  elementAl = new G4Element("Aluminium", "Al",13., 26.9815*g/mole);
  elementSi = new G4Element("Silicon",   "Si",14., 28.0855*g/mole);
  elementTi = new G4Element("Titanium",  "Ti",22.,   47.90*g/mole);
  elementV  = new G4Element("Vanadium",  "V", 23., 50.9415*g/mole);
  elementFe = new G4Element("Iron",      "Fe",26.,  55.845*g/mole);
  elementCo = new G4Element("Cobalt",    "Co",27., 58.9332*g/mole);
  elementCu = new G4Element("Copper",    "Cu",29.,   63.55*g/mole);
  elementMo = new G4Element("Molybdenum","Mo",42.,   95.94*g/mole);
  elementPt = new G4Element("Platinum",  "Pt",78.,  195.08*g/mole);
  elementAu = new G4Element("Gold",      "Au",79.,  196.97*g/mole);
  elementPb = new G4Element("Lead",      "Pb",82.,  207.2*g/mole);

  // Materials

  //  vacuum = new G4Material("vacuum", 1, 1.00794*g/mole, 
  //     1.0E-25*g/cm3, kStateGas, 0.1*kelvin, 1.0E-19*pascal);

  HpGe = new G4Material("HpGe", 32., 72.61*g/mole, 5.323*g/cm3);
  //  pmtMat = new G4Material("pmtMat", 13., 26.982*g/mole, 1.35*g/cm3);   //LR  (Air, copper, and aluminum?)
  pmtMat = new G4Material("pmtMat", 26., 26.982*g/mole, 1.35*g/cm3);   //LR  (Air, copper, and aluminum?)

  LH = new G4Material("LH", 2., 2.0159*g/mole, 70.99*mg/cm3);

  G10 = new G4Material("G10", 1.70*g/cm3, 4);
  G10->AddElement(elementSi, 1);
  G10->AddElement(elementO, 2);
  G10->AddElement(elementC, 3);
  G10->AddElement(elementH, 3);

  ssteel = new G4Material("ssteel", 7.7*g/cm3, 3);
  ssteel->AddElement(elementC, 0.04);
  ssteel->AddElement(elementFe, 0.88);
  ssteel->AddElement(elementCo, 0.08);

  // define materials from the G4 NIST database
  NISTman = G4NistManager::Instance();

  CsI           = NISTman->FindOrBuildMaterial("G4_CESIUM_IODIDE");
  NaI           = NISTman->FindOrBuildMaterial("G4_SODIUM_IODIDE");
  MgO           = NISTman->FindOrBuildMaterial("G4_MAGNESIUM_OXIDE");
  vacuum        = NISTman->FindOrBuildMaterial("G4_Galactic");
  polyethylene  = NISTman->FindOrBuildMaterial("G4_POLYETHYLENE");
  polypropylene = NISTman->FindOrBuildMaterial("G4_POLYPROPYLENE");

  Be = new G4Material("Be",  4., 9.012182*g/mole,  1.84*g/cm3);
  C  = new G4Material("C",   6., 12.011*g/mole,    2.15*g/cm3);
  Al = new G4Material("Al", 13., 26.98153*g/mole,  2.70*g/cm3);
  Si = new G4Material("Si", 14., 28.0855*g/mole,   2.33*g/cm3);
  Cu = new G4Material("Cu", 29., 63.55*g/mole,     8.96*g/cm3);
  Nb = new G4Material("Nb", 41., 92.90638*g/mole,  8.57*g/cm3);
  Au = new G4Material("Au", 79., 196.9*g/mole,    19.32*g/cm3);
  Ir = new G4Material("Ir", 77., 192.217*g/mole,  22.65*g/cm3);
  Pb = new G4Material("Pb", 82., 207.2*g/mole,    11.34*g/cm3);

}

 Materials::~ Materials()
{;}
//-----------------------------------------------------------------------------
G4Material*  Materials::FindMaterial(G4String materialName)
{

   // search the material by its name 
  G4Material* pttoMaterial = G4Material::GetMaterial(materialName);  

  return pttoMaterial;
  
}
