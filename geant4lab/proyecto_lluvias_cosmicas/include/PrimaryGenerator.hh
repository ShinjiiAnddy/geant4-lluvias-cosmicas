#ifndef PRIMARY_GENERATOR_HH
#define PRIMARY_GENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4Event.hh"

class PrimaryGenerator : public G4VUserPrimaryGeneratorAction {
public:
    PrimaryGenerator();
    ~PrimaryGenerator() override;
    void GeneratePrimaries(G4Event* anEvent) override;

private:
    G4ParticleGun* fParticleGun;
};

#endif
