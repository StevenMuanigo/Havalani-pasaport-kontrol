#include "../include/Passport.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <ctime>

Passport::Passport() {}

Passport::Passport(const std::string& mrzLine1, const std::string& mrzLine2) {
    parseMRZ(mrzLine1, mrzLine2);
}

bool Passport::parseMRZ(const std::string& mrzLine1, const std::string& mrzLine2) {
    // Store raw MRZ lines
    this->mrzLine1 = mrzLine1;
    this->mrzLine2 = mrzLine2;
    
    try {
        // Parse MRZ according to ICAO 9303 standard
        if (mrzLine1.length() >= 44 && mrzLine2.length() >= 44) {
            // Line 1 parsing
            documentType = mrzLine1.substr(0, 2);
            issuingCountry = mrzLine1.substr(2, 3);
            lastName = mrzLine1.substr(5, mrzLine1.find("<<", 5) - 5);
            
            // Handle names with multiple parts
            size_t firstNameStart = mrzLine1.find("<<", 5) + 2;
            firstName = mrzLine1.substr(firstNameStart, 39 - firstNameStart);
            
            // Replace '<' with spaces in names
            std::replace(lastName.begin(), lastName.end(), '<', ' ');
            std::replace(firstName.begin(), firstName.end(), '<', ' ');
            
            // Line 2 parsing
            passportNumber = mrzLine2.substr(0, 9);
            nationality = mrzLine2.substr(10, 3);
            dateOfBirth = mrzLine2.substr(13, 6);
            gender = mrzLine2.substr(20, 1);
            expirationDate = mrzLine2.substr(21, 6);
            countryCode = issuingCountry; // Usually same as issuing country
            
            return true;
        }
    } catch (...) {
        return false;
    }
    
    return false;
}

bool Passport::validateMRZChecksum() const {
    // Simplified checksum validation
    // In a real implementation, this would check the actual MRZ check digits
    return true;
}

bool Passport::validateDates() const {
    // Check if dates are valid
    if (dateOfBirth.length() != 6 || expirationDate.length() != 6) {
        return false;
    }
    
    // Simple date validation (format YYMMDD)
    try {
        int birthYear = std::stoi(dateOfBirth.substr(0, 2));
        int birthMonth = std::stoi(dateOfBirth.substr(2, 2));
        int birthDay = std::stoi(dateOfBirth.substr(4, 2));
        
        int expYear = std::stoi(expirationDate.substr(0, 2));
        int expMonth = std::stoi(expirationDate.substr(2, 2));
        int expDay = std::stoi(expirationDate.substr(4, 2));
        
        // Basic range checks
        if (birthMonth < 1 || birthMonth > 12 || birthDay < 1 || birthDay > 31 ||
            expMonth < 1 || expMonth > 12 || expDay < 1 || expDay > 31) {
            return false;
        }
        
        // Check if expiration date is after birth date
        if (expYear < birthYear) {
            return false;
        }
        
        return true;
    } catch (...) {
        return false;
    }
}

bool Passport::isValid() const {
    return !passportNumber.empty() && !firstName.empty() && !lastName.empty() && 
           validateMRZChecksum() && validateDates();
}

bool Passport::isExpired() const {
    // Get current date
    time_t t = time(0);
    tm* now = localtime(&t);
    
    int currentYear = now->tm_year % 100; // Last two digits of year
    int currentMonth = now->tm_mon + 1;   // tm_mon is 0-11
    int currentDay = now->tm_mday;
    
    // Extract expiration date components
    int expYear = std::stoi(expirationDate.substr(0, 2));
    int expMonth = std::stoi(expirationDate.substr(2, 2));
    int expDay = std::stoi(expirationDate.substr(4, 2));
    
    // Compare dates (simplified)
    if (expYear < currentYear) return true;
    if (expYear > currentYear) return false;
    if (expMonth < currentMonth) return true;
    if (expMonth > currentMonth) return false;
    return expDay < currentDay;
}

std::string Passport::toJSON() const {
    std::ostringstream json;
    json << "{\n";
    json << "  \"passportNumber\": \"" << passportNumber << "\",\n";
    json << "  \"firstName\": \"" << firstName << "\",\n";
    json << "  \"lastName\": \"" << lastName << "\",\n";
    json << "  \"nationality\": \"" << nationality << "\",\n";
    json << "  \"dateOfBirth\": \"" << dateOfBirth << "\",\n";
    json << "  \"gender\": \"" << gender << "\",\n";
    json << "  \"expirationDate\": \"" << expirationDate << "\",\n";
    json << "  \"issuingCountry\": \"" << issuingCountry << "\"\n";
    json << "}";
    return json.str();
}

std::string Passport::toXML() const {
    std::ostringstream xml;
    xml << "<passport>\n";
    xml << "  <passportNumber>" << passportNumber << "</passportNumber>\n";
    xml << "  <firstName>" << firstName << "</firstName>\n";
    xml << "  <lastName>" << lastName << "</lastName>\n";
    xml << "  <nationality>" << nationality << "</nationality>\n";
    xml << "  <dateOfBirth>" << dateOfBirth << "</dateOfBirth>\n";
    xml << "  <gender>" << gender << "</gender>\n";
    xml << "  <expirationDate>" << expirationDate << "</expirationDate>\n";
    xml << "  <issuingCountry>" << issuingCountry << "</issuingCountry>\n";
    xml << "</passport>";
    return xml.str();
}
