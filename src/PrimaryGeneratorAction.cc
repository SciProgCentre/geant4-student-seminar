//
// Created by zelenyy on 24.01.2020.
//

#include <G4Gamma.hh>
#include "PrimaryGeneratorAction.hh"
#include "G4SystemOfUnits.hh"

void PrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent) {
   fParticleGun->GeneratePrimaryVertex(anEvent);
}

PrimaryGeneratorAction::PrimaryGeneratorAction() : G4VUserPrimaryGeneratorAction() {
    G4int n_particle = 1;
    fParticleGun  = new G4ParticleGun(n_particle);
    fParticleGun->SetParticleDefinition(G4Gamma::Definition());
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
    fParticleGun->SetParticleEnergy(60.*MeV);
}
