//
// Created by zelenyy on 24.01.2020.
//

#include <G4NistManager.hh>
#include <G4Box.hh>
#include <G4PVPlacement.hh>
#include <G4UniformMagField.hh>
#include "G4FieldManager.hh"
#include <G4TransportationManager.hh>
#include <G4MultiFunctionalDetector.hh>
#include <G4PSEnergyDeposit.hh>
#include <G4SDManager.hh>
#include <CalorimeterSd.hh>
#include <TrackingSd.hh>
#include "G4LogicalVolume.hh"
#include "DetectorConstruction.hh"
#include "G4SystemOfUnits.hh"

G4VPhysicalVolume *DetectorConstruction::Construct() {

    // Option to switch on/off checking of volumes overlaps
    G4bool checkOverlaps = true;

    //
    // World
    //
    G4double world_sizeXY = 3 * meter;
    G4double world_sizeZ = 5 * meter;

    G4Box *solidWorld = new G4Box(
            "world",                       //its name
            0.5 * world_sizeXY,
            0.5 * world_sizeXY,
            0.5 * world_sizeZ);     //its size

    G4LogicalVolume *logicWorld = new G4LogicalVolume(
            solidWorld,          //its solid
            vacuum,           //its material
            "world");            //its name

    G4VPhysicalVolume *physWorld = new G4PVPlacement(
            0,                     //no rotation
            G4ThreeVector(),       //at (0,0,0)
            logicWorld,            //its logical volume
            "world",               //its name
            0,                     //its mother  volume
            false,                 //no boolean operation
            0,                     //copy number
            checkOverlaps);        //overlaps checking

    auto detectorLogic = CreateDetector();

    auto rightDetector = new G4PVPlacement(0, G4ThreeVector(0, 0, detector_length / 2 + 0.1 * meter), detectorLogic,
                                           "rightDetector", logicWorld, false, 0);

    auto rotation =  new G4RotationMatrix(3.14,3.14,0);

//    auto leftDetector = new G4PVPlacement(rotation, G4ThreeVector(0, 0, -detector_length / 2 - 0.1 * meter), detectorLogic,
//                                          "leftDetector", logicWorld, false, 1);

    return physWorld;
}

G4LogicalVolume *DetectorConstruction::CreateDetector() {
    auto detectorSolid = new G4Box("detector", 0.5 * detector_side_size, 0.5 * detector_side_size,
                                   0.5 * detector_length);
    auto detector = new G4LogicalVolume(detectorSolid, vacuum, "detector");

    auto segmentLogic = CreateCalorimeterSection();

    for (int i = 0; i < calorimeter_number_of_segment; ++i) {
        std::string name = "segment_";
        name += std::to_string(i);
        auto segmentPhys = new G4PVPlacement(
                0,
                G4ThreeVector(0, 0,
                              10 * cm + (calorimeter_plastic_thickness +
                                         calorimeter_lead_thickness) * i),
                segmentLogic, name, detector, false, i);
    }

    auto trackingSegmentLogic = CreateTrackingSection();
    auto trackingLeftPhys = new G4PVPlacement(
            0,
            G4ThreeVector(0, 0, -0.5 * meter),
            trackingSegmentLogic,
            "rightSegmentTracking",
            detector,
            false,
            0
    );

    auto trackingRigthPhys = new G4PVPlacement(
            0,
            G4ThreeVector(0, 0, -0.5 * meter + distance_tracking_area),
            trackingSegmentLogic,
            "leftSegmentTracking",
            detector,
            false,
            0
    );

    auto magnetLogic = CreateMagnet();
    auto magnetPhys = new G4PVPlacement(
            0,
            G4ThreeVector(0, 0, -0.5 * meter + 0.5*distance_tracking_area),
            magnetLogic,
            "magnet",
            detector,
            false,
            0
    );

    return detector;
}

DetectorConstruction::DetectorConstruction() {
    // Get nist material manager
    auto nist = G4NistManager::Instance();
    vacuum = nist->FindOrBuildMaterial("G4_Galactic");
    lead = nist->FindOrBuildMaterial("G4_Pb");
    plastic = nist->FindOrBuildMaterial("G4_POLYSTYRENE");
    silicon = nist->FindOrBuildMaterial("G4_Si");


}

G4LogicalVolume *DetectorConstruction::CreateCalorimeterSection() {

    auto segmentSolid = new G4Box("segment", 0.5 * detector_side_size, 0.5 * detector_side_size,
                                  0.5 * (calorimeter_lead_thickness + calorimeter_plastic_thickness));
    auto segmentLogic = new G4LogicalVolume(segmentSolid, vacuum, "segment");
    auto leadSolid = new G4Box("lead", 0.5 * detector_side_size, 0.5 * detector_side_size,
                               0.5 * calorimeter_lead_thickness);
    auto plasticSolid = new G4Box("plastic", 0.5 * detector_side_size, 0.5 * detector_side_size,
                                  0.5 * calorimeter_plastic_thickness);
    auto leadLogic = new G4LogicalVolume(leadSolid, lead, "lead");

    plasticLogic = new G4LogicalVolume(plasticSolid, plastic, "plastic");

    auto leadPhys = new G4PVPlacement(0, G4ThreeVector(0, 0, -calorimeter_lead_thickness / 2), leadLogic, "lead",
                                      segmentLogic, false, 0);
    auto plasticPhys = new G4PVPlacement(0, G4ThreeVector(0, 0, calorimeter_plastic_thickness / 2), plasticLogic,
                                         "plastic", segmentLogic, false, 0);

    return segmentLogic;
}

G4LogicalVolume *DetectorConstruction::CreateTrackingSection() {
    auto segmentSolid = new G4Box("segmentTracking", 0.5 * detector_side_size, 0.5 * detector_side_size,
                                  0.5 * (distance_tracking_layer + 2 * tracking_thickness));

    auto segmentLogic = new G4LogicalVolume(segmentSolid, vacuum, "segmentTracking");

    auto layerLogic = CreateTrackingLayer();

    auto rightLayer = new G4PVPlacement(
            0,
            G4ThreeVector(0, 0, -0.5 * (distance_tracking_layer + tracking_thickness)),
            layerLogic,
            "rightLayer",
            segmentLogic,
            false,
            0
    );
    auto leftLayer = new G4PVPlacement(
            0,
            G4ThreeVector(0, 0, 0.5 * (distance_tracking_layer + tracking_thickness)),
            layerLogic,
            "leftLayer",
            segmentLogic,
            false,
            0
    );

    return segmentLogic;
}

G4LogicalVolume *DetectorConstruction::CreateTrackingLayer() {
    auto layerSolid = new G4Box("layer", 0.5 * detector_side_size, 0.5 * detector_side_size,
                                0.5 * tracking_thickness);
    auto layerLogic = new G4LogicalVolume(layerSolid, vacuum, "layer");
    auto siliconSolid = new G4Box("silicon", 0.5 * tracking_cell_size, 0.5 * tracking_cell_size,
                                  0.5 * tracking_thickness);

    siliconLogic = new G4LogicalVolume(siliconSolid, lead, "silicon");

    for (int i = 0; i < number_of_tracking_cell; ++i) {
        for (int j = 0; j < number_of_tracking_cell; ++j) {
            auto siliconPhys = new G4PVPlacement(
                    0,
                    G4ThreeVector(
                            tracking_cell_size / 2 + i * tracking_cell_size -
                            tracking_cell_size * (number_of_tracking_cell / 2),
                            tracking_cell_size / 2 + j * tracking_cell_size -
                            tracking_cell_size * (number_of_tracking_cell / 2),
                            0),
                    siliconLogic,
                    "silicon",
                    layerLogic,
                    false,
                    i * number_of_tracking_cell + j);
        }
    }


    return layerLogic;
}

void DetectorConstruction::ConstructSDandField() {
    G4VUserDetectorConstruction::ConstructSDandField();
    G4MagneticField *magField;
    magField = new G4UniformMagField(G4ThreeVector(0., 70.0 * kilogauss, 0.0));
    auto fieldMgr = new G4FieldManager;
    fieldMgr->SetDetectorField(magField);
    fieldMgr->CreateChordFinder(magField);
    magnetLogic->SetFieldManager(fieldMgr, true);
    SetupDetectors();
}

void DetectorConstruction::SetupDetectors() {
    auto sdman = G4SDManager::GetSDMpointer();
    auto calorimeterSD = new CalorimeterSD("/calorimeter");
    sdman->AddNewDetector(calorimeterSD);
    plasticLogic->SetSensitiveDetector(calorimeterSD);

    auto trackingSd = new TrackingSD("/tracking");
    sdman->AddNewDetector(trackingSd);
    siliconLogic->SetSensitiveDetector(trackingSd);

}

G4LogicalVolume *DetectorConstruction::CreateMagnet() {
    auto magnetSolid = new G4Box("magnet", 0.5 * detector_side_size, 0.5 * detector_side_size,
                                   1*cm);

    magnetLogic = new G4LogicalVolume(magnetSolid, vacuum, "magnet");
    return magnetLogic;
}


