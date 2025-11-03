#include "../include/VerificationSystem.h"
#include <iostream>
#include <fstream>
#include <algorithm>

VerificationSystem::VerificationSystem() {
    // Initialize with some default visa requirements
    visaRequirements["USA"] = true;  // US citizens need visa for most countries
    visaRequirements["CAN"] = true;  // Canadian citizens
    visaRequirements["GBR"] = true;  // UK citizens
    visaRequirements["AUS"] = true;  // Australian citizens
    visaRequirements["DEU"] = false; // German citizens (EU)
    visaRequirements["FRA"] = false; // French citizens (EU)
    // Add more as needed
    
    // Add some default authorized personnel
    authorizedPersonnel.push_back("SEC001");
    authorizedPersonnel.push_back("SEC002");
    authorizedPersonnel.push_back("ADM001");
}

void VerificationSystem::loadVisaRequirements() {
    // In a real implementation, this would load from a file or database
    // For now, we're using hardcoded values
    std::cout << "Loading visa requirements from database...\n";
}

bool VerificationSystem::requiresVisa(const std::string& countryCode) const {
    auto it = visaRequirements.find(countryCode);
    if (it != visaRequirements.end()) {
        return it->second;
    }
    // Default: require visa if not in our list
    return true;
}

bool VerificationSystem::checkVisaStatus(const Passport& passport) const {
    // In a real implementation, this would check against a visa database
    // For now, we'll simulate a check
    std::string nationality = passport.getNationality();
    
    // Citizens of the issuing country don't need a visa
    if (nationality == passport.getIssuingCountry()) {
        return true;
    }
    
    // Check if visa is required for this nationality
    return !requiresVisa(nationality);
}

bool VerificationSystem::verifyDocumentAuthenticity(const Passport& passport) const {
    // Check if the passport has valid MRZ
    if (!passport.validateMRZChecksum()) {
        return false;
    }
    
    // Check if dates are valid
    if (!passport.validateDates()) {
        return false;
    }
    
    // Additional authenticity checks would go here
    // For example: checking against a database of valid passport numbers
    
    return true;
}

bool VerificationSystem::detectCounterfeit(const Passport& passport) const {
    // Basic counterfeit detection rules
    // 1. Check if passport is expired
    if (passport.isExpired()) {
        return true;
    }
    
    // 2. Check for invalid characters in fields
    const std::string validChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789< ";
    std::string passportData = passport.getPassportNumber() + passport.getFirstName() + 
                              passport.getLastName() + passport.getNationality();
    
    for (char c : passportData) {
        if (validChars.find(toupper(c)) == std::string::npos) {
            return true; // Invalid character found
        }
    }
    
    // 3. Additional checks would go here in a real implementation
    // - Check against databases of stolen passports
    // - Verify security features
    // - Check for tampering
    
    return false; // Not counterfeit
}

void VerificationSystem::addAuthorizedPersonnel(const std::string& id) {
    authorizedPersonnel.push_back(id);
}

bool VerificationSystem::isAuthorizedPersonnel(const std::string& id) const {
    return std::find(authorizedPersonnel.begin(), authorizedPersonnel.end(), id) != 
           authorizedPersonnel.end();
}

VerificationSystem::VerificationResult VerificationSystem::verifyPassport(
    const Passport& passport, const std::string& personnelId) const {
    
    // Check if personnel is authorized
    if (!isAuthorizedPersonnel(personnelId)) {
        return DENIED;
    }
    
    // Check if passport data is valid
    if (!passport.isValid()) {
        return INVALID_DOCUMENT;
    }
    
    // Check for counterfeit
    if (detectCounterfeit(passport)) {
        return DENIED;
    }
    
    // Check document authenticity
    if (!verifyDocumentAuthenticity(passport)) {
        return INVALID_DOCUMENT;
    }
    
    // Check visa status
    if (!checkVisaStatus(passport)) {
        return MANUAL_REVIEW; // Might need manual verification for visa
    }
    
    return APPROVED;
}
