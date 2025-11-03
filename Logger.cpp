#include "../include/Logger.h"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>

Logger::Logger(const std::string& filename) : filename(filename), currentLevel(INFO) {
    logFile.open(filename, std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "Failed to open log file: " << filename << std::endl;
    }
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

void Logger::setLogLevel(LogLevel level) {
    currentLevel = level;
}

void Logger::log(LogLevel level, const std::string& message) {
    if (level < currentLevel) {
        return; // Don't log messages below the current level
    }
    
    std::lock_guard<std::mutex> lock(logMutex);
    
    std::string timestamp = getCurrentTimestamp();
    std::string levelStr = levelToString(level);
    
    std::string logMessage = "[" + timestamp + "] [" + levelStr + "] " + message;
    
    // Output to console
    std::cout << logMessage << std::endl;
    
    // Output to file if open
    if (logFile.is_open()) {
        logFile << logMessage << std::endl;
        logFile.flush();
    }
}

void Logger::debug(const std::string& message) {
    log(DEBUG, message);
}

void Logger::info(const std::string& message) {
    log(INFO, message);
}

void Logger::warning(const std::string& message) {
    log(WARNING, message);
}

void Logger::error(const std::string& message) {
    log(ERROR, message);
}

std::string Logger::levelToString(LogLevel level) {
    switch (level) {
        case DEBUG:   return "DEBUG";
        case INFO:    return "INFO";
        case WARNING: return "WARNING";
        case ERROR:   return "ERROR";
        default:      return "UNKNOWN";
    }
}

std::string Logger::getCurrentTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}
