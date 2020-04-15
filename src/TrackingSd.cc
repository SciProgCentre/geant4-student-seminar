//
// Created by zelenyy on 04.02.2020.
//

#include <include/TrackingSd.hh>
#include <G4Gamma.hh>
#include "TrackingSd.hh"



void TrackingSD::Initialize(G4HCofThisEvent *event) {
    G4VSensitiveDetector::Initialize(event);
    for (int i=0; i<4; i++){
        leftData[i] = empty;
        rightData[i] = empty;
    }
    left_indx = 0;
    rigth_indx = 0;
}

void TrackingSD::EndOfEvent(G4HCofThisEvent *event) {
    G4VSensitiveDetector::EndOfEvent(event);

    auto analysisManager = tupleId->analysisManager;
//    std::cout << "End event" << std::endl;
    bool write_flag = false;
    for (int i=0; i<4; i++){
        if (rightData[i].time >0){
            write_flag = true;
        }
    }
    if (write_flag){
        for (int i=0; i<4; i++){
            int id = tupleId->rightTrackId;
            auto it = rightData[i];
            analysisManager->FillNtupleDColumn(id, 0, it.position.getX());
            analysisManager->FillNtupleDColumn(id, 1, it.position.getY());
            analysisManager->FillNtupleDColumn(id, 2, it.position.getZ());
            analysisManager->FillNtupleDColumn(id, 3,it.time);
            analysisManager->FillNtupleIColumn(id, 4, eventID);
            analysisManager->AddNtupleRow(id);

        }
    }
    write_flag = false;
    for (int i=0; i<4; i++){
        if (leftData[i].time >0){
            write_flag = true;
        }
    }
    if (write_flag) {
        for (int i = 0; i < 4; i++) {
            int id = tupleId->leftTrackId;
            auto it = leftData[i];
            analysisManager->FillNtupleDColumn(id, 0, it.position.getX());
            analysisManager->FillNtupleDColumn(id, 1, it.position.getY());
            analysisManager->FillNtupleDColumn(id, 2, it.position.getZ());
            analysisManager->FillNtupleDColumn(id, 3, it.time);
            analysisManager->FillNtupleIColumn(id, 4, eventID);
            analysisManager->AddNtupleRow(id);
        }
    }
    eventID++;


//    std::cout << leftData.size() << " " << rightData.size() << std::endl;
}

G4bool TrackingSD::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist) {
    if (aStep->GetTrack()->GetParentID() == 0 && aStep->GetTrack()->GetDefinition() != G4Gamma::Definition()){ //Трюк что бы отсечь остальные частицы
//        std::cout << aStep->GetTrack()->GetVolume()->GetCopyNo()<<" ";
//        std::cout << aStep->GetTrack()->GetTouchable()->GetVolume(1)->GetName()<<" ";
//        std::cout << aStep->GetTrack()->GetTouchable()->GetVolume(2)->GetName()<<" ";
//        std::cout << aStep->GetTrack()->GetTouchable()->GetVolume(3)->GetName()<<std::endl;
        int detectorNumber = aStep->GetTrack()->GetTouchable()->GetVolume(3)->GetCopyNo();
        int segmentNumber = aStep->GetTrack()->GetTouchable()->GetVolume(2)->GetCopyNo();
        int layerNumber = aStep->GetTrack()->GetTouchable()->GetVolume(1)->GetCopyNo();
        int cellNumber = aStep->GetTrack()->GetVolume()->GetCopyNo();
//
        TrackingData trackingData;
        trackingData.position = aStep->GetTrack()->GetPosition();
        trackingData.deposit = aStep->GetTotalEnergyDeposit();
        trackingData.time = aStep->GetTrack()->GetGlobalTime();
        if (detectorNumber == 0){
            if (rigth_cur_z == 0){
                rigth_cur_z = trackingData.position.getZ();
                rightData[0] = trackingData;
                rigth_indx++;
            }
            else{
                if (rigth_indx !=4){
                    if (abs(rigth_cur_z - trackingData.position.getZ()) > 2*tracking_thickness){
                        rigth_cur_z =  trackingData.position.getZ();
                        rightData[rigth_indx] = trackingData;
                        rigth_indx++;
                    }
                }

            }

        } else{
            if (left_cur_z == 0){
                left_cur_z = trackingData.position.getZ();
                leftData[0] = trackingData;
                left_indx++;
            }
            else{
                if (left_indx != 4){
                    if (abs(left_cur_z - trackingData.position.getZ()) > 2*tracking_thickness){
                        left_cur_z =  trackingData.position.getZ();
                        leftData[left_indx] = trackingData;
                        left_indx++;
                    }
                }

            }

        }
    }

    return 0;
}
