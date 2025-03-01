#pragma once

#include <string>
#include <vector>
#include <functional>
/**
 * Responsibility: Accept raw log entries from the web server, pass the data to the logParser. 
 * Reads logs from a file and passes each entry to a callback function
 */
class LogReceiver {
public:
    using LogCallback = std::function<void(const std::string&)>;

    explicit LogReceiver(const std::string& source);
    
    void setCallback(LogCallback callback);
    void startReceiving();
    
private:
    std::string source;
    LogCallback logCallback;
    
    void processFile(); // Reads logs from a file
};
