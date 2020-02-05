//
// Created by zelenyy on 04.02.2020.
//

#include "TrackingSd.hh"

void TrackingSD::Initialize(G4HCofThisEvent *event) {
    G4VSensitiveDetector::Initialize(event);
}

void TrackingSD::EndOfEvent(G4HCofThisEvent *event) {
    G4VSensitiveDetector::EndOfEvent(event);
}

G4bool TrackingSD::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist) {
        std::cout << aStep->GetTrack()->GetVolume()->GetCopyNo()<<" ";
    std::cout << aStep->GetTrack()->GetTouchable()->GetVolume(1)->GetName()<<" ";
    std::cout << aStep->GetTrack()->GetTouchable()->GetVolume(2)->GetName()<<" ";
    std::cout << aStep->GetTrack()->GetTouchable()->GetVolume(3)->GetName()<<std::endl;

    auto detectorNumber = aStep->GetTrack()->GetTouchable()->GetVolume(3)->GetCopyNo();
    auto semgentNumber = aStep->GetTrack()->GetTouchable()->GetVolume(2)->GetCopyNo();
    auto layerNumber =  aStep->GetTrack()->GetTouchable()->GetVolume(1)->GetCopyNo();
    auto cellNumber =  aStep->GetTrack()->GetVolume()->GetCopyNo();

    return 0;
}
