//
// Created by zelenyy on 24.01.2020.
//

#ifndef PI_DECAY_DETECTORCONSTRUCTION_HH
#define PI_DECAY_DETECTORCONSTRUCTION_HH


#include <G4VUserDetectorConstruction.hh>
#include "G4LogicalVolume.hh"
#include "TupleId.hh"
#include "GeometrySize.hh"
#include "G4SystemOfUnits.hh"

using namespace CLHEP;


class TrackingCellCoord{
private:
    G4ThreeVector coords[2][2][2][100];
public:
    G4ThreeVector getCoord(int detector, int segment, int layer, int cell){
        return coords[detector][segment][layer][cell];
    }
    void setCoord(int detector, int segment, int layer, int cell,G4ThreeVector coord){
        coords[detector][segment][layer][cell] = coord;
    }
};

class DetectorConstruction : public G4VUserDetectorConstruction{
public:

    G4VPhysicalVolume *Construct() override;

    void ConstructSDandField() override;

    explicit DetectorConstruction(TupleId* tupleId): tupleId(tupleId){
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
    G4LogicalVolume *segmentLogic;

    void InitializeMaterials();

    G4LogicalVolume* CreateMagnet();
    void SetupDetectors();
    TupleId* tupleId;
    TrackingCellCoord* coords;

    void SetTrackingCellCoord();
};


#endif //PI_DECAY_DETECTORCONSTRUCTION_HH
