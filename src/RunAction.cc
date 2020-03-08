//
// Created by zelenyy on 05.02.2020.
//

#include <DetectorConstruction.hh>
#include "RunAction.hh"
#include "g4analysis.hh"


void RunAction::BeginOfRunAction(const G4Run *aRun) {
    G4UserRunAction::BeginOfRunAction(aRun);
    G4AnalysisManager* analysisManager = G4Analysis::ManagerInstance("root");
    analysisManager->OpenFile("PiDecay");
    tupleId->analysisManager = analysisManager;
    // For calorimeter
    int number = DetectorConstruction::calorimeter_number_of_segment;
    int leftCalId = analysisManager->CreateNtuple("LC", "Left calorimeter");
    for (int i = 0; i<number; ++i){
        analysisManager->CreateNtupleDColumn("LC" + std::to_string(i));
    }
    analysisManager->FinishNtuple(leftCalId);


    int rightCalId = analysisManager->CreateNtuple("RC", "Right calorimeter");
    for (int i = 0; i<number; ++i){
        analysisManager->CreateNtupleDColumn("RC" + std::to_string(i));
    }
    analysisManager->FinishNtuple(rightCalId);


    tupleId->leftCalId = leftCalId;
    tupleId->rightCalId = rightCalId;
    // End calorimeter

}

void RunAction::EndOfRunAction(const G4Run *aRun) {
    G4UserRunAction::EndOfRunAction(aRun);
    G4AnalysisManager* analysisManager = G4Analysis::ManagerInstance("root");
    analysisManager->Write();
    analysisManager->CloseFile(true);
}

RunAction::RunAction(TupleId *tupleId) : tupleId(tupleId) {

}
