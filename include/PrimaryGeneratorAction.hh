//
// Created by zelenyy on 24.01.2020.
//

#ifndef PI_DECAY_PRIMARYGENERATORACTION_HH
#define PI_DECAY_PRIMARYGENERATORACTION_HH


#include <G4VUserPrimaryGeneratorAction.hh>
#include <G4ParticleGun.hh>

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction{
public:
    PrimaryGeneratorAction();
    void GeneratePrimaries(G4Event *anEvent) override;

private:
    G4ParticleGun* fParticleGun;
};


#endif //PI_DECAY_PRIMARYGENERATORACTION_HH
