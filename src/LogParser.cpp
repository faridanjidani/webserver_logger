#include "LogParser.hpp"
#include <regex>
#include <sstream>
#include <iomanip>

// @todo farid: check the regex pattern
std::optional<LogEntry> LogParser::parseLogEntry(const std::string& rawLog) {
    std::regex logPattern(R"((\S+) \[(.*?)\] \"(\S+) (\S+) \S+\" (\d+) .*?)");
    std::smatch match;

    if (std::regex_match(rawLog, match, logPattern)) {
        LogEntry entry;
        entry.host = match[1].str();
        entry.timestamp = convertTimestamp(match[2].str());
        entry.method = match[3].str();
        entry.uri = match[4].str();
        entry.statusCode = std::stoi(match[5].str());

        return entry;
    }

    return std::nullopt; // Invalid log format
}

std::string LogParser::convertTimestamp(const std::string& rawTimestamp) {
    int day, hour, minute, second;
    
    // Parse the input format [day:hour:minute:second]
    char ignore;
    std::istringstream ss(rawTimestamp);
    ss  >> day >> ignore >> hour >> ignore >> minute >> ignore >> second >> ignore;

    int year = 2024, month = 8; 
    int baseDay = 1;
    
    // Compute the actual date
    int finalDay = baseDay + day - 1; 

    // Format the new timestamp
    std::ostringstream formattedTime;
    formattedTime << std::setw(4) << year << "-"
                  << std::setw(2) << std::setfill('0') << month << "-"
                  << std::setw(2) << std::setfill('0') << finalDay << " "
                  << std::setw(2) << std::setfill('0') << hour << ":"
                  << std::setw(2) << std::setfill('0') << minute << ":"
                  << std::setw(2) << std::setfill('0') << second;
    
    return formattedTime.str();
}
