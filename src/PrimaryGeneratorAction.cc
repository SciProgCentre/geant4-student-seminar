//
// Created by zelenyy on 24.01.2020.
//

#include <G4Gamma.hh>
#include <G4Electron.hh>
#include <G4PionZero.hh>
#include <G4DynamicParticle.hh>
#include "PrimaryGeneratorAction.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"

void PrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent) {
    if (settings->mode == "gps") {
        particleSource->GeneratePrimaryVertex(anEvent);
    } else {

        G4VDecayChannel *channel = table->GetDecayChannel(settings->channel);
        G4DecayProducts *children;
        bool flag = false;
        do {
            flag = false;
            children = channel->DecayIt(G4PionZero::Definition()->GetPDGMass());
            for (int i = 0; i < children->entries(); ++i) {
                G4DynamicParticle *particle = children->operator[](i);
                auto momentum = particle->GetMomentumDirection();
                double theta  = momentum.theta() / radian;
                if ((theta > 0.1 && theta < pi - 0.1)) {
                    flag = true;
                }
            }
        } while (flag);
        for (int i = 0; i < children->entries(); ++i) {
            G4DynamicParticle *particle = children->operator[](i);
            fParticleGun->SetParticleMomentumDirection(particle->GetMomentumDirection());
            fParticleGun->SetParticleEnergy(particle->GetKineticEnergy());
            fParticleGun->SetParticleDefinition(particle->GetDefinition());
            fParticleGun->GeneratePrimaryVertex(anEvent);
        }

    }
}

PrimaryGeneratorAction::PrimaryGeneratorAction(Settings *settings)
        : G4VUserPrimaryGeneratorAction(), settings(settings) {
    particleSource = new G4GeneralParticleSource();
    G4int n_particle = 1;
    fParticleGun = new G4ParticleGun(n_particle);

    piDecay = new PiDecayGenerator();

    table = G4PionZero::Definition()->GetDecayTable();

    particleTable = G4ParticleTable::GetParticleTable();
}
