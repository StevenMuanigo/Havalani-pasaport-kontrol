#include "../include/PassportControlSystem.h"
#include <iostream>
#include <memory>

int main() {
    std::cout << "Airport Passport Control System\n";
    std::cout << "===============================\n\n";
    
    // Create and initialize the passport control system
    auto system = std::make_unique<PassportControlSystem>();
    
    if (!system->initialize()) {
        std::cerr << "Failed to initialize the system!\n";
        return 1;
    }
    
    std::cout << "System initialized successfully.\n\n";
    
    // Run simulation
    system->runSimulation();
    
    // Shutdown system
    system->shutdown();
    
    std::cout << "\nSystem shutdown complete.\n";
    return 0;
}
