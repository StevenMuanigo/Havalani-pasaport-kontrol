Include Dizini (Header Dosyaları)
## 1. Passport.h
Passport sınıfı tanımı
MRZ alanları (documentType, countryCode, passportNumber, vs.)
Getter ve setter metodları
MRZ çözümleme fonksiyonları
Doğrulama metodları (isValid, isExpired)
JSON/XML dönüşüm fonksiyonları
## 2. VerificationSystem.h
VerificationSystem sınıfı tanımı
Vize durumu kontrolü için visaRequirements map'i
Yetkili personel listesi
Belge doğrulama metodları
Sahtecilik tespiti fonksiyonları
Ana doğrulama işlemi (verifyPassport)
## 3. Logger.h
Logger sınıfı tanımı
Farklı log seviyeleri (DEBUG, INFO, WARNING, ERROR)
Dosya ve konsol loglama
Thread-safe loglama için mutex
## 4. HardwareInterface.h
HardwareInterface sınıfı tanımı
Kamera simülasyonu yapıları (CameraImage)
Belge tarayıcı simülasyonu (ScanData)
RFID okuyucu simülasyonu (RFIDData)
Donanım durumu kontrol fonksiyonları
Simülasyon metodları
## 5. PassportControlSystem.h
Ana sistem sınıfı tanımı
Bileşen yönetimi (verifier, logger, hardware)
Sistem başlatma/kapatma fonksiyonları
Pasaport işleme fonksiyonları
Donanım entegrasyonu metodları
Src Dizini (Kaynak Dosyaları) 

## 1. main.cpp
Programın ana giriş noktası
Sistem başlatma ve kapatma
Simülasyon modu çalıştırma
## 2. Passport.cpp
Passport sınıfı implementasyonu
MRZ çözümleme algoritması
Tarih doğrulama fonksiyonları
JSON/XML dönüşüm implementasyonları
## 3. VerificationSystem.cpp
Doğrulama sistem implementasyonu
Vize durumu kontrol algoritmaları
Sahtecilik tespit kuralları
Yetkili personel kontrolü
## 4. Logger.cpp
Loglama sistem implementasyonu
Zaman damgası oluşturma
Dosya ve konsol yazma işlemleri
Thread-safe loglama
## 5. HardwareInterface.cpp
Donanım simülasyon implementasyonu
Kamera simülasyonu
Belge tarama simülasyonu
RFID okuma simülasyonu
## 6. PassportControlSystem.cpp
Ana sistem kontrol implementasyonu
Bileşen entegrasyonu
Pasaport işleme akışı
Raporlama sistemleri
