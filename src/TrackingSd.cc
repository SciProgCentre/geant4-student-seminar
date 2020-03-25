//
// Created by zelenyy on 04.02.2020.
//

#include <include/TrackingSd.hh>
#include <G4Gamma.hh>
#include "TrackingSd.hh"



void TrackingSD::Initialize(G4HCofThisEvent *event) {
    G4VSensitiveDetector::Initialize(event);
    data.clear();
}

void TrackingSD::EndOfEvent(G4HCofThisEvent *event) {
    G4VSensitiveDetector::EndOfEvent(event);

    auto analysisManager = tupleId->analysisManager;
    std::cout << "End event" << std::endl;
    for (auto it : data){
        auto addres = it.adress;
        auto c = coords->getCoord(addres.detector, addres.segment, addres.layer, addres.cell);
        int id;
        if (addres.detector == 0){
            id = tupleId->rightTrackId;
        }
        else{
            id = tupleId->leftTrackId;
        }
        analysisManager->FillNtupleDColumn(id, 0, c.getX());
        analysisManager->FillNtupleDColumn(id, 1, c.getY());
        analysisManager->FillNtupleDColumn(id, 2, c.getZ());
        analysisManager->FillNtupleDColumn(id, 3,it.time);

    }
    analysisManager->AddNtupleRow(tupleId->leftTrackId);
    analysisManager->AddNtupleRow(tupleId->rightTrackId);

}

G4bool TrackingSD::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist) {
    if (aStep->GetTrack()->GetParentID() == 0 && aStep->GetTrack()->GetDefinition() != G4Gamma::Definition()){ //Трюк что бы отсечь остальные частицы
        std::cout << aStep->GetTrack()->GetVolume()->GetCopyNo()<<" ";
        std::cout << aStep->GetTrack()->GetTouchable()->GetVolume(1)->GetName()<<" ";
        std::cout << aStep->GetTrack()->GetTouchable()->GetVolume(2)->GetName()<<" ";
        std::cout << aStep->GetTrack()->GetTouchable()->GetVolume(3)->GetName()<<std::endl;
        int detectorNumber = aStep->GetTrack()->GetTouchable()->GetVolume(3)->GetCopyNo();
        int segmentNumber = aStep->GetTrack()->GetTouchable()->GetVolume(2)->GetCopyNo();
        int layerNumber = aStep->GetTrack()->GetTouchable()->GetVolume(1)->GetCopyNo();
        int cellNumber = aStep->GetTrack()->GetVolume()->GetCopyNo();

        Adress adress;
        adress.detector = detectorNumber;
        adress.segment = segmentNumber;
        adress.layer = layerNumber;
        adress.cell = cellNumber;
        TrackingData trackingData;
        trackingData.adress = adress;
        trackingData.deposit = aStep->GetTotalEnergyDeposit();
        trackingData.time = aStep->GetTrack()->GetGlobalTime();
        data.push_back(trackingData);
    }

    return 0;
}
