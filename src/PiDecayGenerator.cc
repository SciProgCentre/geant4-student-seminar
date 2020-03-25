//
// Created by zelenyy on 25.03.2020.
//
#include <G4PhysicalConstants.hh>
#include "PiDecayGenerator.hh"
#include "Randomize.hh"

std::vector<Particle> PiDecayGenerator::DecayPi() {
    double sample = rand->flat();
    if(sample < GammaGammaChanelProb ){
        return DecayPiOnTwoGammas();
    }
    else{
        return DecayPiOnElectronesAndGamma();
    }
}

PiDecayGenerator::PiDecayGenerator() {
    rand = G4Random::getTheEngine();
}

std::vector<Particle> PiDecayGenerator::DecayPiOnTwoGammas() {
    double p = piMass/2;

    Particle gamma1;
    Particle gamma2;

    //Разыграем теперь угол вылета для каждого фотона
    double phi = 2*3.1415*rand->flat();
    double theta = acos(2*rand->flat()-1);

    gamma1.energy = p;
    gamma1.pdgid = 22;
    gamma1.momentum = G4ThreeVector(
            p*sin(theta)*cos(phi),
            p*sin(theta)*sin(phi),
            p*cos(theta)
            );

    gamma2.energy = p;
    gamma2.pdgid = 22;
    gamma2.momentum = -1 * gamma1.momentum;
    return std::vector<Particle>({gamma1, gamma2});
}

std::vector<Particle> PiDecayGenerator::DecayPiOnElectronesAndGamma() {
    Particle gamma;
    Particle electron;
    Particle positron;

    TGenPhaseSpace* event = new TGenPhaseSpace();
    TLorentzVector W(0.,0.,0.,piMass);
    double masses[3] = {electron_mass_c2, electron_mass_c2, 0};
    event->SetDecay(W,3,masses);

    while (true){
        double weight = event->Generate();
        if (rand->flat() < weight){
            auto decay = event->GetDecay(0);
            electron = Particle::fromDecay(11, decay);
            decay = event->GetDecay(1);
            positron = Particle::fromDecay(-11, decay);
            decay = event->GetDecay(2);
            gamma = Particle::fromDecay(22, decay);
            break;
        }
    }
    return std::vector<Particle>({gamma, electron, positron});
}
