#include "StatsCollector.hpp"
#include <iostream>

void StatsCollector::addMetric(std::unique_ptr<IMetric> metric) {
    metrics.push_back(std::move(metric));
}

void StatsCollector::processLogEntry(const LogEntry& entry) {
    for (auto& metric : metrics) {
        metric->processEntry(entry);
    }
}


int StatsCollector::getSuccessfulURIAccessCount(const std::string& uri) const {
    auto it = successfulUriAccessCount.find(uri);
    return (it != successfulUriAccessCount.end()) ? it->second : 0;
}

int StatsCollector::getHostAccessCount(const std::string& host) const {
    auto it = hostAccessCount.find(host);
    return (it != hostAccessCount.end()) ? it->second : 0;
}

void StatsCollector::incrementSuccessfulURIAccess(const std::string& uri) {
    successfulUriAccessCount[uri]++;
}

void StatsCollector::incrementHostAccess(const std::string& host) {
    hostAccessCount[host]++;
}


std::unordered_map<std::string, int> StatsCollector::getAllHostAccess() const {
    return hostAccessCount;
}

std::unordered_map<std::string, int> StatsCollector::getAllSuccessfulURIAccess() const {
    return successfulUriAccessCount;
}