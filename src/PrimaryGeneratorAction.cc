#include "PrimaryGeneratorAction.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction(DetectorConstruction *detector): myDetector(detector)
{
  sourcePosition.setX(0);
  sourcePosition.setY(2.54*.1875/2.*cm); // Half capsule depth
  sourcePosition.setZ(0);
  SetSource();
  SetSourceCs137();
  sourceType = "cs137";
  n_particle = 1;
  particleGun = new G4ParticleGun(n_particle);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete particleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{

  particleTable = G4ParticleTable::GetParticleTable();

  // G4cout<<" +++++ In Generate Primaries "<<G4endl;

  // G4cout<<" +++++ Shooting gammas "<<G4endl;
  particleGun->SetParticleDefinition(particleTable->FindParticle("gamma"));
     
  particleGun->SetParticleMomentumDirection(G4RandomDirection());
  particleGun->SetParticlePosition(sourcePosition);
  particleGun->SetParticleEnergy(GetSourceEnergy());

  // G4cout<<" +++++ Generating an event "<<G4endl;
  particleGun->GeneratePrimaryVertex(anEvent);
  // G4cout<<" +++++ Out Generate Primaries "<<G4endl;
}
//---------------------------------------------------------------------
void PrimaryGeneratorAction::SourceReport()
{
  if(source)
    {
      G4cout<<"----> Source type is set to "<< sourceType << G4endl;
      G4cout<<"----> Source position in X is set to "<<G4BestUnit(sourcePosition.getX(),"Length")<<G4endl;
      G4cout<<"----> Source position in Y is set to "<<G4BestUnit(sourcePosition.getY(),"Length")<<G4endl;
      G4cout<<"----> Source position in Z is set to "<<G4BestUnit(sourcePosition.getZ(),"Length")<<G4endl;
    }
  else
    G4cout<<"----> In-beam run selected for simulations"<<G4endl;
}
//-------------------------------------------------------------
void PrimaryGeneratorAction::SetSourceType(G4String name)
{

  sourceType = name;

  if(name == "eu152") {
    SetSourceEu152();
  } else if (name == "cs137") {
    SetSourceCs137();
  } else if (name == "co56") {
    SetSourceCo56();
  } else if (name == "co60") {
    SetSourceCo60();
  } else if (name == "simple") {
    SetSourceSimple();
  }
  
}
//-------------------------------------------------------------
void PrimaryGeneratorAction::SetSourceEu152()
{
  G4double e;
  sourceBranchingSum=0.;

  // start from the beginning of the array
  vector<SourceData*>::iterator itPos = TheSource.begin();
  // clear all elements from the array
  for(; itPos < TheSource.end(); itPos++)
    delete *itPos;    // free the element from memory
   // finally, clear all elements from the array
  TheSource.clear();

  e=121.7830*keV;sourceBranchingSum+=13607.;                  //LR  13620.
  TheSource.push_back(new SourceData(e,sourceBranchingSum));
  e= 244.6920*keV; sourceBranchingSum+= 3602.;                //LR   3590.
  TheSource.push_back(new SourceData(e,sourceBranchingSum));
  e= 295.9390*keV; sourceBranchingSum+=  211.;
  TheSource.push_back(new SourceData(e,sourceBranchingSum));
  e= 344.2760*keV; sourceBranchingSum+=12748.;                //LR  12750.
  TheSource.push_back(new SourceData(e,sourceBranchingSum));
  e= 367.7890*keV; sourceBranchingSum+=  405.;
  TheSource.push_back(new SourceData(e,sourceBranchingSum));
  e= 411.1150*keV; sourceBranchingSum+= 1071.;                //LR   1071.
  TheSource.push_back(new SourceData(e,sourceBranchingSum));
  e= 443.9760*keV; sourceBranchingSum+= 1497.;                //LR   1480.
  TheSource.push_back(new SourceData(e,sourceBranchingSum));
  e= 488.6610*keV; sourceBranchingSum+=  195.;
  TheSource.push_back(new SourceData(e,sourceBranchingSum));
  e= 564.0210*keV; sourceBranchingSum+=  236.;
  TheSource.push_back(new SourceData(e,sourceBranchingSum));
  e= 586.2940*keV; sourceBranchingSum+=  220.;
  TheSource.push_back(new SourceData(e,sourceBranchingSum));
  e= 678.5780*keV; sourceBranchingSum+=  221.;
  TheSource.push_back(new SourceData(e,sourceBranchingSum));
  e= 688.6780*keV; sourceBranchingSum+=  400.;
  TheSource.push_back(new SourceData(e,sourceBranchingSum));
  e= 778.9030*keV; sourceBranchingSum+= 6216.;                //LR   6190.
  TheSource.push_back(new SourceData(e,sourceBranchingSum));
  e= 867.3880*keV; sourceBranchingSum+= 1990.;
  TheSource.push_back(new SourceData(e,sourceBranchingSum));
  e= 964.1310*keV; sourceBranchingSum+= 7012.;                //LR   6920.
  TheSource.push_back(new SourceData(e,sourceBranchingSum));
  e=1005.2790*keV; sourceBranchingSum+=  310.;
  TheSource.push_back(new SourceData(e,sourceBranchingSum));
  e=1085.8000*keV; sourceBranchingSum+= 4873.;                //LR  1089.7, 820.
  TheSource.push_back(new SourceData(e,sourceBranchingSum));
  e=1109.1800*keV; sourceBranchingSum+=   88.;
  TheSource.push_back(new SourceData(e,sourceBranchingSum));
  e=1112.1160*keV; sourceBranchingSum+= 6490.;
  TheSource.push_back(new SourceData(e,sourceBranchingSum));
  e=1212.9500*keV; sourceBranchingSum+=  670.;
  TheSource.push_back(new SourceData(e,sourceBranchingSum));
  e=1299.1240*keV; sourceBranchingSum+=  780.;
  TheSource.push_back(new SourceData(e,sourceBranchingSum));
  e=1408.0110*keV; sourceBranchingSum+=10000.;
  TheSource.push_back(new SourceData(e,sourceBranchingSum));
}
//-------------------------------------------------------------
void PrimaryGeneratorAction::SetSourceCs137()
{
  G4double e;
  sourceBranchingSum=0.;

  // start from the beginning of the array
  vector<SourceData*>::iterator itPos = TheSource.begin();
  // clear all elements from the array
  for(; itPos < TheSource.end(); itPos++)
    delete *itPos;    // free the element from memory
   // finally, clear all elements from the array
  TheSource.clear();

  e=661.657*keV;sourceBranchingSum+=100.;
  TheSource.push_back(new SourceData(e,sourceBranchingSum));
}
//-------------------------------------------------------------
void PrimaryGeneratorAction::SetSourceCo56()
{
  G4double e;
  sourceBranchingSum=0.;

  // start from the beginning of the array
  vector<SourceData*>::iterator itPos = TheSource.begin();
  // clear all elements from the array
  for(; itPos < TheSource.end(); itPos++)
    delete *itPos;    // free the element from memory
   // finally, clear all elements from the array
  TheSource.clear();

  e=846.771*keV;sourceBranchingSum+=99.935;
  TheSource.push_back(new SourceData(e,sourceBranchingSum));
  e=977.373*keV; sourceBranchingSum+= 1.449;
  TheSource.push_back(new SourceData(e,sourceBranchingSum));
  e=1037.840*keV; sourceBranchingSum+= 14.17;
  TheSource.push_back(new SourceData(e,sourceBranchingSum));
  e=1175.102*keV; sourceBranchingSum+=2.288;
  TheSource.push_back(new SourceData(e,sourceBranchingSum));
  e=1238.282*keV; sourceBranchingSum+=66.9;
  TheSource.push_back(new SourceData(e,sourceBranchingSum));
  e=1360.215*keV; sourceBranchingSum+=4.29;
  TheSource.push_back(new SourceData(e,sourceBranchingSum));
  e=1771.351*keV; sourceBranchingSum+=15.47;
  TheSource.push_back(new SourceData(e,sourceBranchingSum));
  e=2015.181*keV; sourceBranchingSum+=3.04;
  TheSource.push_back(new SourceData(e,sourceBranchingSum));
  e=2034.755*keV; sourceBranchingSum+=7.89;
  TheSource.push_back(new SourceData(e,sourceBranchingSum));
  e=2598.459*keV; sourceBranchingSum+=17.3;
  TheSource.push_back(new SourceData(e,sourceBranchingSum));
  e=3009.596*keV; sourceBranchingSum+=1.16;
  TheSource.push_back(new SourceData(e,sourceBranchingSum));
  e=3201.962*keV; sourceBranchingSum+=3.32;
  TheSource.push_back(new SourceData(e,sourceBranchingSum));
  e=3253.416*keV; sourceBranchingSum+=8.12;
  TheSource.push_back(new SourceData(e,sourceBranchingSum));
  e=3272.990*keV; sourceBranchingSum+=1.93;
  TheSource.push_back(new SourceData(e,sourceBranchingSum));
  e=3451.152*keV; sourceBranchingSum+=0.972;
}
//-------------------------------------------------------------
void PrimaryGeneratorAction::SetSourceCo60()
{
  G4double e;
  sourceBranchingSum=0.;

  // start from the beginning of the array
  vector<SourceData*>::iterator itPos = TheSource.begin();
  // clear all elements from the array
  for(; itPos < TheSource.end(); itPos++)
    delete *itPos;    // free the element from memory
   // finally, clear all elements from the array
  TheSource.clear();

  e=1173.228*keV;sourceBranchingSum+=99.85;
  TheSource.push_back(new SourceData(e,sourceBranchingSum));
  e=1332.492*keV; sourceBranchingSum+=99.9826;
  TheSource.push_back(new SourceData(e,sourceBranchingSum));
}
void PrimaryGeneratorAction::SetSourceSimple()
{
  G4double e;
  sourceBranchingSum=0.;

  // start from the beginning of the array
  vector<SourceData*>::iterator itPos = TheSource.begin();
  // clear all elements from the array
  for(; itPos < TheSource.end(); itPos++)
    delete *itPos;    // free the element from memory
   // finally, clear all elements from the array
  TheSource.clear();

  e=1000.0*keV;sourceBranchingSum+=100.;
  TheSource.push_back(new SourceData(e,sourceBranchingSum));
}
//-------------------------------------------------------------------------
G4double PrimaryGeneratorAction::GetSourceEnergy()
{
 
  G4double rand;

  rand=G4UniformRand()*sourceBranchingSum;

  vector<SourceData*>::iterator itPos = TheSource.begin();

  for(; itPos < TheSource.end(); itPos++)
    if(rand<(*itPos)->b) return (*itPos)->e;

  cout << "******** Oops!!!!" << endl;

  return -1*keV;
}
//-------------------------------------------------------------------------
void PrimaryGeneratorAction::SetSourceEnergy(G4double energy)
{
  if(sourceType == "simple"){
     vector<SourceData*>::iterator itPos = TheSource.begin();
     (*itPos)->e = energy;
     G4cout << "Setting source energy to " << energy << " MeV" << G4endl;
  } else {
    G4cout << "Warning: /Experiment/Source/setEnergy has no effect unless the source type is set to \"simple\"" << G4endl;
  }
}
//-------------------------------------------------------------------------
void PrimaryGeneratorAction::SetSourceX(G4double x)
{
  sourcePosition.setX(x);
  myDetector->getSourceCapsule()->setX(x);
}
//-------------------------------------------------------------------------
void PrimaryGeneratorAction::SetSourceY(G4double y)
{
  sourcePosition.setY(y);
  myDetector->getSourceCapsule()->setY(y);
}
//-------------------------------------------------------------------------
void PrimaryGeneratorAction::SetSourceZ(G4double z)
{
  sourcePosition.setZ(z);
  myDetector->getSourceCapsule()->setZ(z);
}
//-------------------------------------------------------------------------
