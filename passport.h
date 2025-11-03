#ifndef PASSPORT_H
#define PASSPORT_H

#include <string>
#include <vector>
#include <map>

class Passport {
private:
    std::string passportNumber;
    std::string firstName;
    std::string lastName;
    std::string nationality;
    std::string dateOfBirth;
    std::string gender;
    std::string expirationDate;
    std::string issuingCountry;
    std::string mrzLine1;
    std::string mrzLine2;
    
    // MRZ fields
    std::string documentType;
    std::string countryCode;
    std::string passportIdentifier;
    std::string optionalData;
    std::string compositeCheckDigit;

public:
    Passport();
    Passport(const std::string& mrzLine1, const std::string& mrzLine2);
    
    // Getters
    std::string getPassportNumber() const { return passportNumber; }
    std::string getFirstName() const { return firstName; }
    std::string getLastName() const { return lastName; }
    std::string getNationality() const { return nationality; }
    std::string getDateOfBirth() const { return dateOfBirth; }
    std::string getGender() const { return gender; }
    std::string getExpirationDate() const { return expirationDate; }
    std::string getIssuingCountry() const { return issuingCountry; }
    std::string getMrzLine1() const { return mrzLine1; }
    std::string getMrzLine2() const { return mrzLine2; }
    std::string getDocumentType() const { return documentType; }
    std::string getCountryCode() const { return countryCode; }
    
    // Setters
    void setPassportNumber(const std::string& number) { passportNumber = number; }
    void setFirstName(const std::string& name) { firstName = name; }
    void setLastName(const std::string& name) { lastName = name; }
    void setNationality(const std::string& nation) { nationality = nation; }
    void setDateOfBirth(const std::string& dob) { dateOfBirth = dob; }
    void setGender(const std::string& g) { gender = g; }
    void setExpirationDate(const std::string& exp) { expirationDate = exp; }
    void setIssuingCountry(const std::string& country) { issuingCountry = country; }
    
    // MRZ Processing
    bool parseMRZ(const std::string& mrzLine1, const std::string& mrzLine2);
    bool validateMRZChecksum() const;
    bool validateDates() const;
    
    // Validation
    bool isValid() const;
    bool isExpired() const;
    
    // Utility
    std::string toJSON() const;
    std::string toXML() const;
};

#endif // PASSPORT_H
