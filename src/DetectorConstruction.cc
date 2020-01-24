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
    // Get nist material manager
    auto nist = G4NistManager::Instance();

    // Option to switch on/off checking of volumes overlaps
    G4bool checkOverlaps = true;

    //
    // World
    //
    G4double world_sizeXY = 20*meter;
    G4double world_sizeZ  = 30*meter;
    G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");

    G4Box* solidWorld =
            new G4Box("World",                       //its name
                      0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     //its size

    G4LogicalVolume* logicWorld =
            new G4LogicalVolume(solidWorld,          //its solid
                                world_mat,           //its material
                                "World");            //its name

    G4VPhysicalVolume* physWorld =
            new G4PVPlacement(0,                     //no rotation
                              G4ThreeVector(),       //at (0,0,0)
                              logicWorld,            //its logical volume
                              "World",               //its name
                              0,                     //its mother  volume
                              false,                 //no boolean operation
                              0,                     //copy number
                              checkOverlaps);        //overlaps checking
    return physWorld;
}
