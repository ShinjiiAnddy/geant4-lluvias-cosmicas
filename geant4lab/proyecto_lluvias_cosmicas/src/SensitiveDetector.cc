#include "SensitiveDetector.hh"

#include "G4Step.hh"
#include "G4Track.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"

SensitiveDetector::SensitiveDetector(G4String name) : G4VSensitiveDetector(name) {
    numberOfParticles = 0;
}

SensitiveDetector::~SensitiveDetector() {}

G4bool SensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory*) {
    numberOfParticles++;

    G4Track* track = step->GetTrack();
    G4String particleName = track->GetDefinition()->GetParticleName();
    G4double particleEnergy = track->GetTotalEnergy();
    G4double energyDeposit = step->GetTotalEnergyDeposit();

    G4cout << "============================" << G4endl;
    G4cout << "Particula detectada N  : " << numberOfParticles << G4endl;
    G4cout << "Tipo: " << particleName << G4endl;
    G4cout << "Energia de la particula: " << particleEnergy/MeV << " MeV" << G4endl;
    G4cout << "Energia depositada: " << energyDeposit/MeV << " MeV" << G4endl;
    G4cout << "============================" << G4endl;

    return true;
}
