#include "PrimaryGeneratorAction.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction(DetectorConstruction *detector): myDetector(detector)
{
  sourcePosition.setX(0);
  sourcePosition.setY(2.54*.1875/2.*cm); // Half capsule depth
  sourcePosition.setZ(0);
  simpleSourceEnergy = 0;
  muonSourceEnergy = 0;
  sourceType = "decay";
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
  if(sourceType == "simple"){
    particleGun->SetParticleDefinition(particleTable->FindParticle("gamma"));
     
    particleGun->SetParticleMomentumDirection(G4RandomDirection());
    particleGun->SetParticlePosition(sourcePosition);
    particleGun->SetParticleEnergy(simpleSourceEnergy);
  } else if (sourceType == "muon") {
    if(G4UniformRand()<0.5)
      particleGun->SetParticleDefinition(particleTable->FindParticle("mu+"));
    else
      particleGun->SetParticleDefinition(particleTable->FindParticle("mu-"));
    particleGun->SetParticleMomentumDirection(G4RandomDirection());
    particleGun->SetParticlePosition(sourcePosition);
    particleGun->SetParticleEnergy(muonSourceEnergy);
  } else {
    particleGun->SetParticleEnergy(0*eV);
    particleGun->SetParticlePosition(sourcePosition);
    particleGun->SetParticleMomentumDirection(G4ThreeVector(1.,0.,0.));   
  }
  // G4cout<<" +++++ Generating an event "<<G4endl;
  particleGun->GeneratePrimaryVertex(anEvent);
  // G4cout<<" +++++ Out Generate Primaries "<<G4endl;
}
//---------------------------------------------------------------------
void PrimaryGeneratorAction::SourceReport()
{
  if(sourceType == "simple")
    G4cout<<"----> Simple gamma-ray source, energy = "<<simpleSourceEnergy*MeV<<" MeV"<<G4endl;
  else if(sourceType == "muon")
    G4cout<<"----> Muon source, energy = "<<muonSourceEnergy*MeV<<" MeV"<<G4endl;
  G4cout<<"----> Source position in X is set to "<<G4BestUnit(sourcePosition.getX(),"Length")<<G4endl;
  G4cout<<"----> Source position in Y is set to "<<G4BestUnit(sourcePosition.getY(),"Length")<<G4endl;
  G4cout<<"----> Source position in Z is set to "<<G4BestUnit(sourcePosition.getZ(),"Length")<<G4endl;
}
//-------------------------------------------------------------------------
void PrimaryGeneratorAction::SetSourceEnergy(G4double energy)
{
  sourceType = "simple";
  simpleSourceEnergy = energy;
}
//-------------------------------------------------------------------------
void PrimaryGeneratorAction::SetMuonEnergy(G4double energy)
{
  sourceType = "muon";
  muonSourceEnergy = energy;
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
