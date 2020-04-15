//
// Created by zelenyy on 05.02.2020.
//

#include <DetectorConstruction.hh>
#include <include/GeometrySize.hh>
#include "RunAction.hh"
#include "g4analysis.hh"


void RunAction::BeginOfRunAction(const G4Run *aRun) {
    G4UserRunAction::BeginOfRunAction(aRun);
    G4AnalysisManager *analysisManager = G4Analysis::ManagerInstance("root");
    analysisManager->OpenFile(settings->output);
    tupleId->analysisManager = analysisManager;

    /**
     * TODO(Создать таблицы для калориметра)
     * Создайте с помощью analysisManager две таблицы: для правого и левого калориметра
     * В цикле создайте столбец для кадой секции калориметра
     */
    // For calorimeter
    int number = calorimeter_number_of_segment;
    int leftCalId = analysisManager->CreateNtuple("LC", "Left calorimeter");
    for (int i = 0; i < number; ++i) {
        analysisManager->CreateNtupleDColumn("LC" + std::to_string(i));
    }
    analysisManager->FinishNtuple(leftCalId);


    int rightCalId = analysisManager->CreateNtuple("RC", "Right calorimeter");
    for (int i = 0; i < number; ++i) {
        analysisManager->CreateNtupleDColumn("RC" + std::to_string(i));
    }
    analysisManager->FinishNtuple(rightCalId);


    tupleId->leftCalId = leftCalId;
    tupleId->rightCalId = rightCalId;
    // End calorimeter

    //For Tracking
    int leftTrackId = analysisManager->CreateNtuple("LT", "Left tracking detector");
    analysisManager->CreateNtupleDColumn("xL");
    analysisManager->CreateNtupleDColumn("yL");
    analysisManager->CreateNtupleDColumn("zL");
    analysisManager->CreateNtupleDColumn("tL");
    analysisManager->CreateNtupleIColumn("eventL");
    analysisManager->FinishNtuple(leftTrackId);

    int rightTrackId = analysisManager->CreateNtuple("RT", "Right tracking detector");
    analysisManager->CreateNtupleDColumn("xR");
    analysisManager->CreateNtupleDColumn("yR");
    analysisManager->CreateNtupleDColumn("zR");
    analysisManager->CreateNtupleDColumn("tR");
    analysisManager->CreateNtupleIColumn("eventR");
    analysisManager->FinishNtuple(rightTrackId);
    tupleId->leftTrackId = leftTrackId;
    tupleId->rightTrackId = rightTrackId;
    // End  tracking

}

void RunAction::EndOfRunAction(const G4Run *aRun) {
    G4UserRunAction::EndOfRunAction(aRun);
    G4AnalysisManager *analysisManager = G4Analysis::ManagerInstance("root");
    analysisManager->Write();
    analysisManager->CloseFile(true);
}

RunAction::RunAction(TupleId *tupleId, Settings* settings) : tupleId(tupleId), settings(settings) {

}
