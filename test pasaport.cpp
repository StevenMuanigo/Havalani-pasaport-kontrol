#include "../include/Passport.h"
#include "../include/Logger.h"
#include <iostream>
#include <cassert>

void testPassportCreation() {
    std::cout << "Testing Passport Creation...\n";
    
    // Test default constructor
    Passport p1;
    assert(!p1.isValid());
    
    // Test MRZ parsing
    std::string mrz1 = "P<USASMITH<<JOHN<<<<<<<<<<<<<<<<<<<<<<<";
    std::string mrz2 = "P12345678<8USA800101<M251231<<<<<<<<<<";
    
    Passport p2(mrz1, mrz2);
    
    assert(p2.getPassportNumber() == "P12345678");
    assert(p2.getFirstName() == "JOHN");
    assert(p2.getLastName() == "SMITH");
    assert(p2.getNationality() == "USA");
    assert(p2.getDateOfBirth() == "800101");
    assert(p2.getGender() == "M");
    assert(p2.getExpirationDate() == "251231");
    assert(p2.getIssuingCountry() == "USA");
    
    std::cout << "✓ Passport creation tests passed\n";
}

void testJSONOutput() {
    std::cout << "Testing JSON Output...\n";
    
    std::string mrz1 = "P<USASMITH<<JOHN<<<<<<<<<<<<<<<<<<<<<<<";
    std::string mrz2 = "P12345678<8USA800101<M251231<<<<<<<<<<";
    
    Passport p(mrz1, mrz2);
    std::string json = p.toJSON();
    
    // Basic check for JSON structure
    assert(json.find("\"passportNumber\": \"P12345678\"") != std::string::npos);
    assert(json.find("\"firstName\": \"JOHN\"") != std::string::npos);
    assert(json.find("\"lastName\": \"SMITH\"") != std::string::npos);
    
    std::cout << "✓ JSON output tests passed\n";
}

void testXMLOutput() {
    std::cout << "Testing XML Output...\n";
    
    std::string mrz1 = "P<USASMITH<<JOHN<<<<<<<<<<<<<<<<<<<<<<<";
    std::string mrz2 = "P12345678<8USA800101<M251231<<<<<<<<<<";
    
    Passport p(mrz1, mrz2);
    std::string xml = p.toXML();
    
    // Basic check for XML structure
    assert(xml.find("<passportNumber>P12345678</passportNumber>") != std::string::npos);
    assert(xml.find("<firstName>JOHN</firstName>") != std::string::npos);
    assert(xml.find("<lastName>SMITH</lastName>") != std::string::npos);
    
    std::cout << "✓ XML output tests passed\n";
}

void testValidation() {
    std::cout << "Testing Validation...\n";
    
    std::string mrz1 = "P<USASMITH<<JOHN<<<<<<<<<<<<<<<<<<<<<<<";
    std::string mrz2 = "P12345678<8USA800101<M251231<<<<<<<<<<";
    
    Passport p(mrz1, mrz2);
    
    // Valid passport should pass validation
    assert(p.isValid());
    
    // Check if passport is expired (depends on current date)
    // This test might fail in the future when the passport expires
    assert(!p.isExpired()); // Assuming current date is before 2025-12-31
    
    std::cout << "✓ Validation tests passed\n";
}

int main() {
    Logger logger("test.log");
    logger.info("Starting Passport tests");
    
    try {
        testPassportCreation();
        testJSONOutput();
        testXMLOutput();
        testValidation();
        
        std::cout << "\nAll tests passed!\n";
        logger.info("All Passport tests passed");
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        logger.error("Test failed with exception: " + std::string(e.what()));
        return 1;
    }
}
