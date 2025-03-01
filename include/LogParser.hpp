#pragma once

#include <string>
#include <optional>

struct LogEntry {
    std::string host;
    std::string timestamp;
    std::string method;
    std::string uri;
    int statusCode;
};

class LogParser {
public:
    static std::optional<LogEntry> parseLogEntry(const std::string& rawLog);
private:    
    static std::string convertTimestamp(const std::string& rawTimestamp);
};
