#ifndef SENSITIVE_DETECTOR_HH
#define SENSITIVE_DETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "G4Step.hh"

class SensitiveDetector : public G4VSensitiveDetector {
public:
    SensitiveDetector(G4String name);
    ~SensitiveDetector() override;
    G4bool ProcessHits(G4Step* step, G4TouchableHistory* ROhist) override;

private:
    int numberOfParticles;
};

#endif
