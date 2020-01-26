//
// Created by zelenyy on 24.01.2020.
//

#ifndef PI_DECAY_DETECTORCONSTRUCTION_HH
#define PI_DECAY_DETECTORCONSTRUCTION_HH


#include <G4VUserDetectorConstruction.hh>
#include "G4SystemOfUnits.hh"


class DetectorConstruction : public G4VUserDetectorConstruction{
public:
    G4VPhysicalVolume *Construct() override;

    const double detector_side_size = 0.5*meter;
    const double detector_length = 2*meter;
    const double calorimeter_lead_thickness = 1*cm;
    const double calorimeter_plastic_thickness = 1*cm;
    const int number_of_tracking_cell = 10;
    const double tracking_cell_size = 0.05*meter;
    const double tracking_thickness = 0.5*mm;
    const double distance_tracking_layer = 0.10*meter;
    const double distance_tracking_area = 0.20*meter;
    const double distance_tracking_center = 0.20*meter;
    const double distance_tracking_calorimeter = 0.10*meter;


};


#endif //PI_DECAY_DETECTORCONSTRUCTION_HH
