//
// Created by zelenyy on 24.01.2020.
//

#ifndef PI_DECAY_PRIMARYGENERATORACTION_HH
#define PI_DECAY_PRIMARYGENERATORACTION_HH


#include <G4VUserPrimaryGeneratorAction.hh>
#include <G4ParticleGun.hh>
#include <G4GeneralParticleSource.hh>
#include "PiDecayGenerator.hh"
#include "Settings.hh"
#include "G4DecayTable.hh"
#include "G4DecayProducts.hh"

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction{
public:
    explicit PrimaryGeneratorAction(Settings* settings);
    void GeneratePrimaries(G4Event *anEvent) override;
    ~PrimaryGeneratorAction(){
        delete particleSource;
        delete fParticleGun;
    }
private:
    G4ParticleGun* fParticleGun;
    PiDecayGenerator *piDecay;
    G4ParticleTable *particleTable;
    Settings* settings;
    G4GeneralParticleSource *particleSource;
    G4DecayTable *table;
};


#endif //PI_DECAY_PRIMARYGENERATORACTION_HH
