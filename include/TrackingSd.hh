//
// Created by zelenyy on 04.02.2020.
//

#ifndef PI_DECAY_TRACKINGSD_HH
#define PI_DECAY_TRACKINGSD_HH


#include <G4VSensitiveDetector.hh>

class TrackingSD : public G4VSensitiveDetector {
public:
    explicit TrackingSD(std::string name) : G4VSensitiveDetector(name){

    };
    void Initialize(G4HCofThisEvent *event) override;

    void EndOfEvent(G4HCofThisEvent *event) override;

protected:
    G4bool ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist) override;

};


#endif //PI_DECAY_TRACKINGSD_HH
