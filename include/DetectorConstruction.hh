//
// Created by zelenyy on 24.01.2020.
//

#ifndef PI_DECAY_DETECTORCONSTRUCTION_HH
#define PI_DECAY_DETECTORCONSTRUCTION_HH


#include <G4VUserDetectorConstruction.hh>
#include "G4LogicalVolume.hh"


class DetectorConstruction : public G4VUserDetectorConstruction{
public:
    G4VPhysicalVolume *Construct() override;

    void ConstructSDandField() override;

    DetectorConstruction(){
        InitializeMaterials();
    }

private:
    G4Material* vacuum;
    G4Material* lead;
    G4Material* plastic;
    G4Material* silicon;
    G4LogicalVolume* CreateDetector();
    G4LogicalVolume* CreateCalorimeterSection();
    G4LogicalVolume* CreateTrackingLayer();
    G4LogicalVolume* CreateTrackingSection();
    G4LogicalVolume *magnetLogic;
    G4LogicalVolume *plasticLogic;
    G4LogicalVolume *siliconLogic;
    G4LogicalVolume *detectorLogic;

    void InitializeMaterials();

    G4LogicalVolume* CreateMagnet();
    void SetupDetectors();

};


#endif //PI_DECAY_DETECTORCONSTRUCTION_HH
