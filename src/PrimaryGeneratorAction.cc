//
// Created by zelenyy on 24.01.2020.
//

#include <G4Gamma.hh>
#include <G4Electron.hh>
#include "PrimaryGeneratorAction.hh"
#include "G4SystemOfUnits.hh"

void PrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent) {
/**
 * TODO()
 * Ваша задача, используя код который вы написали на прошлых занятиях,
 * генерировать начальные частицы возникающие при распаде Pi мезона.
 */

    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
    fParticleGun->SetParticleEnergy(60.0 * MeV);


    // Генерируем первую первичную частицы для события
    fParticleGun->SetParticleDefinition(G4Electron::Definition());
    fParticleGun->GeneratePrimaryVertex(anEvent);

    // Генерируем вторую первичную частицу для события
    fParticleGun->SetParticleDefinition(G4Gamma::Definition());
    fParticleGun->GeneratePrimaryVertex(anEvent);
}

PrimaryGeneratorAction::PrimaryGeneratorAction() : G4VUserPrimaryGeneratorAction() {

    G4int n_particle = 1;
    fParticleGun = new G4ParticleGun(n_particle);

}
