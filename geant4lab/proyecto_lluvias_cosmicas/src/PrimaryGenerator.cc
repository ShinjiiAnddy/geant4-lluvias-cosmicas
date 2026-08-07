#include "PrimaryGenerator.hh"

#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"

PrimaryGenerator::PrimaryGenerator() {
    fParticleGun = new G4ParticleGun(1);
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* particle = particleTable->FindParticle("proton");

    fParticleGun->SetParticleDefinition(particle);
    fParticleGun->SetParticleEnergy(100*GeV);
    // Disparo desde Z = +40m (por encima de la atmósfera)
    fParticleGun->SetParticlePosition(G4ThreeVector(0, 0, 40*m));
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0, 0, -1));
}

PrimaryGenerator::~PrimaryGenerator() {
    delete fParticleGun;
}

void PrimaryGenerator::GeneratePrimaries(G4Event* anEvent) {
    fParticleGun->GeneratePrimaryVertex(anEvent);
}
