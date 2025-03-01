// IMetric.hpp
#pragma once
#include <vector>
#include <string>
#include "LogParser.hpp"
#include "StatsCollector.hpp"

// Forward declaration of StatsCollector
class StatsCollector;

class IMetric {
protected:
    StatsCollector& statsCollector;
public:
    explicit IMetric(StatsCollector& collector) : statsCollector(collector) {}
    virtual ~IMetric() = default;
    virtual void processEntry(const LogEntry& entry) = 0;
};
