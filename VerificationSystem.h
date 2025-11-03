#ifndef VERIFICATION_SYSTEM_H
#define VERIFICATION_SYSTEM_H

#include "Passport.h"
#include <string>
#include <vector>
#include <map>

class VerificationSystem {
private:
    std::map<std::string, bool> visaRequirements; // Country codes and their visa requirements
    std::vector<std::string> authorizedPersonnel; // IDs of authorized personnel
    
public:
    VerificationSystem();
    
    // Visa status checking
    void loadVisaRequirements(); // Load from file/database
    bool requiresVisa(const std::string& countryCode) const;
    bool checkVisaStatus(const Passport& passport) const;
    
    // Document authenticity checking
    bool verifyDocumentAuthenticity(const Passport& passport) const;
    
    // Counterfeit detection
    bool detectCounterfeit(const Passport& passport) const;
    
    // Personnel authorization
    void addAuthorizedPersonnel(const std::string& id);
    bool isAuthorizedPersonnel(const std::string& id) const;
    
    // Main verification process
    enum VerificationResult {
        APPROVED,
        DENIED,
        MANUAL_REVIEW,
        INVALID_DOCUMENT
    };
    
    VerificationResult verifyPassport(const Passport& passport, const std::string& personnelId) const;
};

#endif // VERIFICATION_SYSTEM_H
