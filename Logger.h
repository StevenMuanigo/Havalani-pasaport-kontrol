#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <mutex>

class Logger {
public:
    enum LogLevel {
        DEBUG,
        INFO,
        WARNING,
        ERROR
    };

private:
    std::ofstream logFile;
    LogLevel currentLevel;
    std::mutex logMutex;
    std::string filename;

public:
    Logger(const std::string& filename = "passport_control.log");
    ~Logger();
    
    void setLogLevel(LogLevel level);
    void log(LogLevel level, const std::string& message);
    void debug(const std::string& message);
    void info(const std::string& message);
    void warning(const std::string& message);
    void error(const std::string& message);
    
private:
    std::string levelToString(LogLevel level);
    std::string getCurrentTimestamp();
};

#endif // LOGGER_H
