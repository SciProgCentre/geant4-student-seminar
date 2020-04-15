//
// Created by zelenyy on 24.01.2020.
//

#include <G4Gamma.hh>
#include <G4Electron.hh>
#include "PrimaryGeneratorAction.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"

void PrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent) {
    if (settings->mode == "gps"){
        particleSource->GeneratePrimaryVertex(anEvent);
    }
    else{
        // Используем генератор распада Пи-мезона
        bool flag = false;
        std::vector<Particle> particle;
        do {
            flag = false;
            particle = piDecay->DecayPi();
            for (auto it: particle) {
                auto momentum = it.momentum;
                if ((momentum.theta() / radian > 0.1 && momentum.theta() / radian < pi - 0.1)) {
                    flag = true;
                }
            }
        } while (flag);

        for (auto it : particle) {
            fParticleGun->SetParticleMomentumDirection(it.momentum);
            fParticleGun->SetParticleEnergy(it.energy);
            auto defenition = particleTable->FindParticle(it.pdgid);
            fParticleGun->SetParticleDefinition(defenition);
            fParticleGun->GeneratePrimaryVertex(anEvent);
        }
    }
}

PrimaryGeneratorAction::PrimaryGeneratorAction(Settings* settings) : G4VUserPrimaryGeneratorAction(), settings(settings) {
    particleSource = new G4GeneralParticleSource();
    G4int n_particle = 1;
    fParticleGun = new G4ParticleGun(n_particle);

    piDecay = new PiDecayGenerator();

    particleTable = G4ParticleTable::GetParticleTable();
}
