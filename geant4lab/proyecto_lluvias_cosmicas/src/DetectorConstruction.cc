#include "DetectorConstruction.hh"
#include "SensitiveDetector.hh"

#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"

DetectorConstruction::DetectorConstruction() {}
DetectorConstruction::~DetectorConstruction() {}

G4VPhysicalVolume* DetectorConstruction::Construct() {
    G4NistManager* nist = G4NistManager::Instance();

    G4Material* air = nist->FindOrBuildMaterial("G4_AIR");
    G4Material* silicon = nist->FindOrBuildMaterial("G4_Si");

    // Mundo: 20m x 20m x 100m (de Z = -50m a Z = +50m)
    G4Box* solidWorld = new G4Box("World", 10*m, 10*m, 50*m);
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, air, "World");
    G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "World", 0, false, 0);

    // Atmósfera: 18m x 18m x 40m (ubicada en Z = +10m, abarca de Z = -10m a Z = +30m)
    G4Box* solidAtmosphere = new G4Box("Atmosphere", 9*m, 9*m, 20*m);
    G4LogicalVolume* logicAtmosphere = new G4LogicalVolume(solidAtmosphere, air, "Atmosphere");
    new G4PVPlacement(0, G4ThreeVector(0,0,10*m), logicAtmosphere, "Atmosphere", logicWorld, false, 0);

    // Detector: 16m x 16m x 1m (ubicado en Z = -20m, abarca de Z = -20.5m a Z = -19.5m)
    G4Box* solidDetector = new G4Box("Detector", 8*m, 8*m, 0.5*m);
    logicDetector = new G4LogicalVolume(solidDetector, silicon, "Detector");
    new G4PVPlacement(0, G4ThreeVector(0,0,-20*m), logicDetector, "Detector", logicWorld, false, 0);

    return physWorld;
}

void DetectorConstruction::ConstructSDandField() {
    SensitiveDetector* detector = new SensitiveDetector("SensitiveDetector");
    G4SDManager::GetSDMpointer()->AddNewDetector(detector);
    logicDetector->SetSensitiveDetector(detector);
}
