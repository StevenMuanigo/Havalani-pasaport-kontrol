#ifndef PASSPORT_CONTROL_SYSTEM_H
#define PASSPORT_CONTROL_SYSTEM_H

#include "Passport.h"
#include "VerificationSystem.h"
#include "Logger.h"
#include "HardwareInterface.h"
#include <memory>
#include <string>

class PassportControlSystem {
private:
    std::unique_ptr<VerificationSystem> verifier;
    std::unique_ptr<Logger> logger;
    std::unique_ptr<HardwareInterface> hardware;
    bool systemActive;
    
public:
    PassportControlSystem();
    ~PassportControlSystem();
    
    // System management
    bool initialize();
    void shutdown();
    bool isSystemActive() const { return systemActive; }
    
    // Main processing functions
    bool processPassport();
    VerificationSystem::VerificationResult verifyPassport(const Passport& passport, 
                                                         const std::string& personnelId);
    
    // Hardware integration
    std::shared_ptr<Passport> scanPassport();
    bool capturePassengerPhoto(const std::string& passportNumber);
    bool readRFIDChip();
    
    // Reporting
    void generateReport() const;
    
    // Simulation mode
    void runSimulation();
};

#endif // PASSPORT_CONTROL_SYSTEM_H
