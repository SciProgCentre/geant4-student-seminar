//
// Created by zelenyy on 05.02.2020.
//

#include "RunAction.hh"
#include "g4analysis.hh"

void RunAction::BeginOfRunAction(const G4Run *aRun) {
    G4UserRunAction::BeginOfRunAction(aRun);
    G4AnalysisManager* analysisManager = G4Analysis::ManagerInstance("root");
    analysisManager->OpenFile("PiDecay");

}

void RunAction::EndOfRunAction(const G4Run *aRun) {
    G4UserRunAction::EndOfRunAction(aRun);
    G4AnalysisManager* analysisManager = G4Analysis::ManagerInstance("root");
    analysisManager->Write();
    analysisManager->CloseFile(true);
}
