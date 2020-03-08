//
// Created by zelenyy on 08.03.2020.
//

#ifndef PI_DECAY_TUPLEID_HH
#define PI_DECAY_TUPLEID_HH

#include "g4analysis.hh"

struct TupleId{
    G4AnalysisManager* analysisManager;
    int leftCalId = -1;
    int rightCalId = -1;
};

#endif //PI_DECAY_TUPLEID_HH
