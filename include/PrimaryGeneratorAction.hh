//
// Created by zelenyy on 24.01.2020.
//

#ifndef PI_DECAY_PRIMARYGENERATORACTION_HH
#define PI_DECAY_PRIMARYGENERATORACTION_HH


#include <G4VUserPrimaryGeneratorAction.hh>
#include <G4ParticleGun.hh>
#include "PiDecayGenerator.hh"

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction{
public:
    /**
     *
     * @param isPiDecay --- если true то используется генератор распада пи-мезона
     */
    explicit PrimaryGeneratorAction(bool isPiDecay = false);
    void GeneratePrimaries(G4Event *anEvent) override;

private:
    bool isPiDecay;
    G4ParticleGun* fParticleGun;
    PiDecayGenerator *piDecay;
    G4ParticleTable *particleTable;
};


#endif //PI_DECAY_PRIMARYGENERATORACTION_HH
