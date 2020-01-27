//
// Created by zelenyy on 24.01.2020.
//

#include <G4NistManager.hh>
#include <G4Box.hh>
#include <G4PVPlacement.hh>
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

    G4Box *solidWorld =
            new G4Box("world",                       //its name
                      0.5 * world_sizeXY, 0.5 * world_sizeXY, 0.5 * world_sizeZ);     //its size

    G4LogicalVolume *logicWorld =
            new G4LogicalVolume(solidWorld,          //its solid
                                vacuum,           //its material
                                "world");            //its name

    G4VPhysicalVolume *physWorld =
            new G4PVPlacement(0,                     //no rotation
                              G4ThreeVector(),       //at (0,0,0)
                              logicWorld,            //its logical volume
                              "world",               //its name
                              0,                     //its mother  volume
                              false,                 //no boolean operation
                              0,                     //copy number
                              checkOverlaps);        //overlaps checking

    auto detectorLogic = CreateDetector();
    auto rightDetector = new G4PVPlacement(0, G4ThreeVector(0,0,detector_length/2 + 0.5*meter), detectorLogic, "right", logicWorld, false, 0);
    return physWorld;
}

G4LogicalVolume *DetectorConstruction::CreateDetector() {
    auto detectorSolid = new G4Box("detector", 0.5*detector_side_size, 0.5*detector_side_size, 0.5*detector_length);
    auto detector = new G4LogicalVolume(detectorSolid, vacuum, "detector");

    auto segmentLogic = CreateCalorimeterSection();

    auto segmentPhys = new G4PVPlacement(0, G4ThreeVector(0,0,10*cm), segmentLogic, "segment", detector, false, 0);

    return detector;
}

DetectorConstruction::DetectorConstruction() {
    // Get nist material manager
    auto nist = G4NistManager::Instance();
    vacuum = nist->FindOrBuildMaterial("G4_Galactic");
    lead = nist->FindOrBuildMaterial("G4_Pb");
    plastic = nist->FindOrBuildMaterial("G4_POLYSTYRENE");

}

G4LogicalVolume *DetectorConstruction::CreateCalorimeterSection() {

    auto segmentSolid =  new G4Box("segment", 0.5*detector_side_size, 0.5*detector_side_size, 0.5*(calorimeter_lead_thickness + calorimeter_plastic_thickness));
    auto segmentLogic =  new G4LogicalVolume(segmentSolid, vacuum, "segment");
    auto leadSolid = new G4Box("lead", 0.5*detector_side_size, 0.5*detector_side_size, 0.5*calorimeter_lead_thickness);
    auto plasticSolid = new G4Box("plastic", 0.5*detector_side_size, 0.5*detector_side_size, 0.5*calorimeter_plastic_thickness);
    auto leadLogic = new G4LogicalVolume(leadSolid, lead, "lead");
    auto plasticLogic = new G4LogicalVolume(plasticSolid, plastic, "lead");

    auto leadPhys = new G4PVPlacement(0, G4ThreeVector(0,0,-calorimeter_lead_thickness/2), leadLogic, "lead", segmentLogic, false, 0);
    auto plasticPhys = new G4PVPlacement(0, G4ThreeVector(0,0,calorimeter_plastic_thickness/2), plasticLogic, "lead", segmentLogic, false, 0);

    return segmentLogic;
}
