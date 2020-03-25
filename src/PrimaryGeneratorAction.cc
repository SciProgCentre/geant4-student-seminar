//
// Created by zelenyy on 24.01.2020.
//

#include <G4Gamma.hh>
#include <G4Electron.hh>
#include "PrimaryGeneratorAction.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
void PrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent) {
/**
 * TODO(Использовать генератор распада пи-мезона)
 * Ваша задача, используя код который вы написали на прошлых занятиях,
 * генерировать начальные частицы возникающие при распаде Pi мезона.
 */
    if (isPiDecay){
        auto particle = piDecay->DecayPi();
        //FIXME(Отказываться от неподходящих событий)

        for (auto it : particle){
            fParticleGun->SetParticleMomentumDirection(it.momentum);
            fParticleGun->SetParticleEnergy(it.energy);
            auto defenition = particleTable->FindParticle(it.pdgid);
            fParticleGun->SetParticleDefinition(defenition);
            fParticleGun->GeneratePrimaryVertex(anEvent);
        }
    } else{
        fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
        fParticleGun->SetParticleEnergy(60.0 * MeV);

        // Генерируем первую первичную частицы для события
        fParticleGun->SetParticleDefinition(G4Electron::Definition());
        fParticleGun->GeneratePrimaryVertex(anEvent);

        // Генерируем вторую первичную частицу для события
        fParticleGun->SetParticleDefinition(G4Gamma::Definition());
        fParticleGun->GeneratePrimaryVertex(anEvent);
    }

}

PrimaryGeneratorAction::PrimaryGeneratorAction(bool isPiDecay) :  G4VUserPrimaryGeneratorAction(), isPiDecay(isPiDecay) {

    G4int n_particle = 1;
    fParticleGun = new G4ParticleGun(n_particle);

    piDecay = new PiDecayGenerator();

    particleTable = G4ParticleTable::GetParticleTable();
}
