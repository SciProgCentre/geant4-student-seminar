//
// Created by zelenyy on 04.02.2020.
//

#ifndef PI_DECAY_CALORIMETERSD_HH
#define PI_DECAY_CALORIMETERSD_HH


#include <G4VSensitiveDetector.hh>
#include "DetectorConstruction.hh"


class CalorimeterSD : public G4VSensitiveDetector{
public:
    explicit CalorimeterSD(std::string name) : G4VSensitiveDetector(name){

    };
    G4bool ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist) override;

    ~CalorimeterSD() override;

    void Initialize(G4HCofThisEvent *event) override;

    void EndOfEvent(G4HCofThisEvent *event) override;

private:
    static const int number = DetectorConstruction::calorimeter_number_of_segment;
    double right[number];
    double left[number];

};


#endif //PI_DECAY_CALORIMETERSD_HH
