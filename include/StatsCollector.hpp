#pragma once
#include "IMetric.hpp"
#include <unordered_map>
#include <vector>
#include <memory>
#include <string>
#include <iostream>

class IMetric;
class StatsCollector {
private:
    std::vector<std::unique_ptr<IMetric>> metrics;
    std::unordered_map<std::string, int> successfulUriAccessCount;
    std::unordered_map<std::string, int> hostAccessCount; 
public:
    void addMetric(std::unique_ptr<IMetric> metric);

    void processLogEntry(const LogEntry& entry);

    int getSuccessfulURIAccessCount(const std::string& uri) const; 
    int getHostAccessCount(const std::string& uri) const;

    void incrementSuccessfulURIAccess(const std::string& uri);
    void incrementHostAccess(const std::string& host);

    // Methods to get all data for fomratted output
    std::unordered_map<std::string, int> getAllHostAccess() const;
    std::unordered_map<std::string, int> getAllSuccessfulURIAccess() const;

};
