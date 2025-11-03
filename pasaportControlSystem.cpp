#include "../include/PassportControlSystem.h"
#include <iostream>
#include <memory>

PassportControlSystem::PassportControlSystem() : systemActive(false) {
    verifier = std::make_unique<VerificationSystem>();
    logger = std::make_unique<Logger>("passport_system.log");
    hardware = std::make_unique<HardwareInterface>();
}

PassportControlSystem::~PassportControlSystem() {
    shutdown();
}

bool PassportControlSystem::initialize() {
    logger->info("Initializing Passport Control System...");
    
    if (!verifier || !logger || !hardware) {
        logger->error("Failed to initialize system components");
        return false;
    }
    
    // Initialize hardware
    hardware->simulateHardwareConnection();
    
    systemActive = true;
    logger->info("Passport Control System initialized successfully");
    return true;
}

void PassportControlSystem::shutdown() {
    if (systemActive) {
        logger->info("Shutting down Passport Control System...");
        systemActive = false;
        logger->info("Passport Control System shut down successfully");
    }
}

bool PassportControlSystem::processPassport() {
    if (!systemActive) {
        logger->error("System is not active");
        return false;
    }
    
    logger->info("Starting passport processing...");
    
    // Scan passport
    auto passport = scanPassport();
    if (!passport) {
        logger->error("Failed to scan passport");
        return false;
    }
    
    // Capture passenger photo
    if (!capturePassengerPhoto(passport->getPassportNumber())) {
        logger->warning("Failed to capture passenger photo");
        // Continue processing even if photo capture fails
    }
    
    // Read RFID chip
    if (!readRFIDChip()) {
        logger->warning("Failed to read RFID chip");
        // Continue processing even if RFID read fails
    }
    
    // Verify passport
    std::string personnelId = "SEC001"; // In a real system, this would be entered by operator
    auto result = verifyPassport(*passport, personnelId);
    
    // Log result
    switch (result) {
        case VerificationSystem::APPROVED:
            logger->info("Passport approved for " + passport->getFirstName() + " " + passport->getLastName());
            break;
        case VerificationSystem::DENIED:
            logger->info("Passport denied for " + passport->getFirstName() + " " + passport->getLastName());
            break;
        case VerificationSystem::MANUAL_REVIEW:
            logger->info("Passport requires manual review for " + passport->getFirstName() + " " + passport->getLastName());
            break;
        case VerificationSystem::INVALID_DOCUMENT:
            logger->info("Invalid document detected for " + passport->getFirstName() + " " + passport->getLastName());
            break;
    }
    
    return true;
}

VerificationSystem::VerificationResult PassportControlSystem::verifyPassport(
    const Passport& passport, const std::string& personnelId) {
    
    logger->info("Verifying passport for " + passport.getFirstName() + " " + passport.getLastName());
    auto result = verifier->verifyPassport(passport, personnelId);
    
    // Log verification details
    logger->debug("Passport Number: " + passport.getPassportNumber());
    logger->debug("Nationality: " + passport.getNationality());
    logger->debug("Expiration Date: " + passport.getExpirationDate());
    
    return result;
}

std::shared_ptr<Passport> PassportControlSystem::scanPassport() {
    logger->info("Scanning passport document...");
    
    auto scanData = hardware->scanDocument();
    if (!scanData) {
        logger->error("Failed to scan document");
        return nullptr;
    }
    
    auto passport = hardware->parseScannedData(*scanData);
    if (!passport) {
        logger->error("Failed to parse scanned data");
        return nullptr;
    }
    
    logger->info("Passport scanned successfully: " + passport->getPassportNumber());
    return passport;
}

bool PassportControlSystem::capturePassengerPhoto(const std::string& passportNumber) {
    logger->info("Capturing passenger photo...");
    
    auto image = hardware->captureImage();
    if (!image) {
        logger->error("Failed to capture passenger photo");
        return false;
    }
    
    std::string filename = "photo_" + passportNumber + ".jpg";
    if (!hardware->saveImage(*image, filename)) {
        logger->error("Failed to save passenger photo");
        return false;
    }
    
    logger->info("Passenger photo captured and saved as " + filename);
    return true;
}

bool PassportControlSystem::readRFIDChip() {
    logger->info("Reading RFID chip...");
    
    auto rfidData = hardware->readRFIDChip();
    if (!rfidData) {
        logger->error("Failed to read RFID chip");
        return false;
    }
    
    logger->info("RFID chip read successfully");
    return true;
}

void PassportControlSystem::generateReport() const {
    logger->info("Generating system report...");
    // In a real implementation, this would generate detailed reports
    std::cout << "=== Passport Control System Report ===\n";
    std::cout << "System Status: " << (systemActive ? "ACTIVE" : "INACTIVE") << "\n";
    std::cout << "Hardware Status: CONNECTED\n";
    std::cout << "Logs saved to: passport_system.log\n";
    std::cout << "=====================================\n";
}

void PassportControlSystem::runSimulation() {
    logger->info("Starting system simulation...");
    
    std::cout << "=== Airport Passport Control System ===\n";
    std::cout << "Simulation Mode\n";
    std::cout << "=======================================\n";
    
    // Process a sample passport
    processPassport();
    
    // Generate report
    generateReport();
    
    logger->info("Simulation completed");
}
