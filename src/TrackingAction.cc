#include "TrackingAction.hh"

TrackingAction::TrackingAction(EventAction* evt){
  eventAction = evt;
}

void TrackingAction::PreUserTrackingAction(const G4Track* aTrack)
{

  eventInfo 
    = (EventInformation*)eventAction->GetEvent()->GetUserInformation();

  // Emitted gamma
  if( ( aTrack->GetParticleDefinition()->GetParticleName() == "gamma" ||
	aTrack->GetParticleDefinition()->GetParticleName() == "neutron" ||
	aTrack->GetParticleDefinition()->GetParticleName() == "mu+" ||
	aTrack->GetParticleDefinition()->GetParticleName() == "mu-" )
      &&
      ( aTrack->GetParentID() == 0 ||
	aTrack->GetCreatorProcess()->GetProcessName() == "RadioactiveDecay" ||
	aTrack->GetCreatorProcess()->GetProcessName() == "Radioactivation") ){

    //    G4cout << "> Event ID = " << eventAction->GetEvent()->GetEventID() << G4endl;

    G4ThreeVector pos = aTrack->GetPosition();
    G4ThreeVector dir = aTrack->GetMomentumDirection();

    // G4cout << std::fixed << std::setprecision(4) 
    // 	   << std::setw(12) << std::right
    // 	   << "   pos = " << pos
    // 	   << "   dir = " << dir
    // 	   << "   energy = " << aTrack->GetKineticEnergy()
    // 	   << "   parent = " << aTrack->GetParentID()
    // 	   << G4endl;

    eventInfo->AddEmittedGamma(aTrack->GetKineticEnergy(), 
			       &pos, &dir,
			       aTrack->GetParentID());

  }
  
}
