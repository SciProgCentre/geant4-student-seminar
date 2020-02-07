//
// Created by zelenyy on 05.02.2020.
//

#ifndef PI_DECAY_RUNACTION_HH
#define PI_DECAY_RUNACTION_HH


#include <G4UserRunAction.hh>

class RunAction : public G4UserRunAction{
public:
    void BeginOfRunAction(const G4Run *aRun) override;

    void EndOfRunAction(const G4Run *aRun) override;

};


#endif //PI_DECAY_RUNACTION_HH
