//
// Created by zelenyy on 15.04.2020.
//

#ifndef PI_DECAY_SETTINGS_HH
#define PI_DECAY_SETTINGS_HH

#include "string"

using namespace std;

class Settings {
public:
    string output = "PiDecay";
    double field = 50.0 * kilogauss;
    string mode = "gps";
};


#endif //PI_DECAY_SETTINGS_HH
