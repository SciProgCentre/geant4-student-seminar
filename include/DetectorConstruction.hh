//
// Created by zelenyy on 24.01.2020.
//

#ifndef PI_DECAY_DETECTORCONSTRUCTION_HH
#define PI_DECAY_DETECTORCONSTRUCTION_HH


#include <G4VUserDetectorConstruction.hh>
#include "G4SystemOfUnits.hh"
#include "G4LogicalVolume.hh"

class DetectorConstruction : public G4VUserDetectorConstruction{
public:
    DetectorConstruction();
    G4VPhysicalVolume *Construct() override;

    void ConstructSDandField() override;

    const double detector_side_size = 0.5*meter;
    const double detector_length = 2*meter;
    const double calorimeter_lead_thickness = 1*cm;
    const double calorimeter_plastic_thickness = 5*cm;
    static const int calorimeter_number_of_segment = 8;
    const int number_of_tracking_cell = 10;
    const double tracking_cell_size = 0.05*meter;
    const double tracking_thickness = 0.5*mm;
    const double distance_tracking_layer = 0.10*meter;
    const double distance_tracking_area = 0.20*meter;
    const double distance_tracking_center = 0.20*meter;
    const double distance_tracking_calorimeter = 0.10*meter;
private:
    G4Material* vacuum;
    G4Material* lead;
    G4Material* plastic;
    G4Material* silicon;
    G4LogicalVolume* CreateDetector();
    G4LogicalVolume* CreateCalorimeterSection();
    G4LogicalVolume* CreateTrackingLayer();
    G4LogicalVolume* CreateTrackingSection();
    G4LogicalVolume* CreateMagnet();
    G4LogicalVolume *magnetLogic;
    G4LogicalVolume *plasticLogic;
    G4LogicalVolume *siliconLogic;
    void SetupDetectors();
};


#endif //PI_DECAY_DETECTORCONSTRUCTION_HH
