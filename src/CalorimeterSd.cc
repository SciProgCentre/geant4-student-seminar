//
// Created by zelenyy on 04.02.2020.
//

#include "CalorimeterSd.hh"

G4bool CalorimeterSD::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist) {
//    std::cout << aStep->GetTrack()->GetVolume()->GetName()<<" ";
//    std::cout << aStep->GetTrack()->GetTouchable()->GetVolume(1)->GetName()<<" ";
//    std::cout << aStep->GetTrack()->GetTouchable()->GetVolume(2)->GetName()<<" ";<<std::endl;

    auto detectorNumber = aStep->GetTrack()->GetTouchable()->GetVolume(2)->GetCopyNo();
    auto semgentNumber = aStep->GetTrack()->GetTouchable()->GetVolume(1)->GetCopyNo();
    if (detectorNumber == 0){
        right[semgentNumber] += aStep->GetTotalEnergyDeposit();
    } else{
        left[semgentNumber] += aStep->GetTotalEnergyDeposit();
    }
    return 0;
}

CalorimeterSD::~CalorimeterSD() {

}

void CalorimeterSD::Initialize(G4HCofThisEvent *event) {
    G4VSensitiveDetector::Initialize(event);

    for (int i = 0; i<number; ++i){
        right[i] = 0;
        left[i] = 0;
    }

}

void CalorimeterSD::EndOfEvent(G4HCofThisEvent *event) {
    G4VSensitiveDetector::EndOfEvent(event);
    for (int i = 0; i<number; ++i){
        std::cout << left[i]<<" "<< right[i]<<std::endl;
        right[i] = 0;
        left[i] = 0;
    }
}
