#ifndef HARDWARE_INTERFACE_H
#define HARDWARE_INTERFACE_H

#include <string>
#include <vector>
#include <memory>

// Forward declarations
class Passport;

class HardwareInterface {
public:
    // Camera simulation
    struct CameraImage {
        std::vector<unsigned char> imageData;
        int width;
        int height;
        std::string format; // "JPEG", "PNG", etc.
    };
    
    // Scanner simulation
    struct ScanData {
        std::string rawData;
        std::string format; // "MRZ", "PDF417", etc.
    };
    
    // RFID/NFC reader simulation
    struct RFIDData {
        std::string chipData;
        std::string securityKeys;
    };

private:
    bool cameraAvailable;
    bool scannerAvailable;
    bool rfidReaderAvailable;
    
public:
    HardwareInterface();
    
    // Camera functions
    bool initializeCamera();
    std::shared_ptr<CameraImage> captureImage();
    bool saveImage(const CameraImage& image, const std::string& filename);
    
    // Scanner functions
    bool initializeScanner();
    std::shared_ptr<ScanData> scanDocument();
    std::shared_ptr<Passport> parseScannedData(const ScanData& data);
    
    // RFID functions
    bool initializeRFIDReader();
    std::shared_ptr<RFIDData> readRFIDChip();
    
    // Hardware status
    bool isCameraAvailable() const { return cameraAvailable; }
    bool isScannerAvailable() const { return scannerAvailable; }
    bool isRFIDReaderAvailable() const { return rfidReaderAvailable; }
    
    // Simulation functions
    void simulateHardwareConnection();
    std::shared_ptr<ScanData> simulateMRZScan();
    std::shared_ptr<CameraImage> simulatePhotoCapture();
};

#endif // HARDWARE_INTERFACE_H
