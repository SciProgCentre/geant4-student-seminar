//
// Created by zelenyy on 05.02.2020.
//

#ifndef PI_DECAY_RUNACTION_HH
#define PI_DECAY_RUNACTION_HH


#include <G4UserRunAction.hh>
#include "TupleId.hh"

class RunAction : public G4UserRunAction{
public:

    explicit RunAction(TupleId* tupleId);

    void BeginOfRunAction(const G4Run *aRun) override;

    void EndOfRunAction(const G4Run *aRun) override;

private:
    TupleId* tupleId;
};


#endif //PI_DECAY_RUNACTION_HH
