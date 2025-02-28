#include "LogParser.hpp"
#include <regex>
#include <sstream>

// @todo farid: check the regex pattern
std::optional<LogEntry> LogParser::parseLogEntry(const std::string& rawLog) {
    std::regex logPattern(R"((\S+) \[(.*?)\] \"(\S+) (\S+) \S+\" (\d+) .*?)");
    std::smatch match;

    if (std::regex_match(rawLog, match, logPattern)) {
        LogEntry entry;
        entry.host = match[1].str();
        entry.timestamp = match[2].str();
        entry.method = match[3].str();
        entry.uri = match[4].str();
        entry.statusCode = std::stoi(match[5].str());

        return entry;
    }

    return std::nullopt; // Invalid log format
}
