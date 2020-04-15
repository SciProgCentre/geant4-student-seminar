//
// Created by zelenyy on 25.03.2020.
//

#ifndef PI_DECAY_PIDECAYGENERATOR_HH
#define PI_DECAY_PIDECAYGENERATOR_HH

#include <G4ThreeVector.hh>
#include "vector"
#include "G4SystemOfUnits.hh"
#include <TGenPhaseSpace.h>
#include <CLHEP/Random/RandomEngine.h>

using namespace CLHEP;

struct Particle{
    int pdgid;
    double energy;
    G4ThreeVector momentum;

    static Particle fromDecay(int pdgid, TLorentzVector *decay){
        Particle particle;
        particle.pdgid = pdgid;
        particle.energy = decay->E();
        particle.momentum = G4ThreeVector(decay->Px(), decay->Py(), decay->Pz());
        return particle;
    }
};



class PiDecayGenerator {
public:
    PiDecayGenerator();
    std::vector<Particle> DecayPi();

private:
    HepRandomEngine* rand;
    const double piMass = 134.9766*MeV;
    const double GammaGammaChanelProb = 0.97;

    std::vector<Particle> DecayPiOnTwoGammas();

    std::vector<Particle> DecayPiOnElectronesAndGamma();
};


#endif //PI_DECAY_PIDECAYGENERATOR_HH
