//
// Created by zelenyy on 04.02.2020.
//

#include "CalorimeterSd.hh"

G4bool CalorimeterSD::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist) {

    // Эти строки можно закомментирововать
//    std::cout <<std::endl;
//    std::cout << "<< Start Calorimeter Hit >>"<<std::endl;
//    std::cout <<"Volume name: "  << aStep->GetTrack()->GetVolume()->GetName()<<std::endl;
//    auto parentVolume = aStep->GetTrack()->GetTouchable()->GetVolume(1);
//    std::cout << "Parent volume name and number: " << parentVolume->GetName()<< " " << parentVolume->GetCopyNo() <<std::endl;
//    auto grandParentVolume = aStep->GetTrack()->GetTouchable()->GetVolume(2);
//    std::cout << "Grandparent volume name and number: " << grandParentVolume->GetName()<<" "<< grandParentVolume->GetCopyNo()<<std::endl;
//    std::cout << "Energy deposit in the step: "<<aStep->GetTotalEnergyDeposit()<<std::endl;
//    std::cout << "<< End Calorimeter Hit >>"<<std::endl;


    // TODO(Используя номера объемов заполните добавьте энерговыделение на этом шаге в массив left или rigth)
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
    // TODO(Очистить массивы перед началом события)
    for (int i = 0; i<number; ++i){
        right[i] = 0;
        left[i] = 0;
    }
}

void CalorimeterSD::EndOfEvent(G4HCofThisEvent *event) {
    G4VSensitiveDetector::EndOfEvent(event);

    /** TODO(Сохраните результат в ROOT файл)
     * Используйте tupleId что бы получить id для получения таблиц энерговыделения в правом и левом калориметре
     * С помошью цикла перенесите содержимое массивов left и rigth
     * в таблицы хранящиеся в analysisManager
    */
    auto analysisManager = tupleId->analysisManager;
    for (int i = 0; i<number; ++i){
//        std::cout << left[i]<<" "<< right[i]<<std::endl;
        analysisManager->FillNtupleDColumn(tupleId->leftCalId, i, left[i]);
        analysisManager->FillNtupleDColumn(tupleId->rightCalId, i, right[i]);
    }
    analysisManager->AddNtupleRow(tupleId->leftCalId);
    analysisManager->AddNtupleRow(tupleId->rightCalId);

}
