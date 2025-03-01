// HostAccessCounter.hpp
#pragma once
#include "IMetric.hpp"
#include <unordered_map>
#include <iostream>

class HostAccessCounter : public IMetric {

public:
    using IMetric::IMetric;  // Inherit constructor
    void processEntry(const LogEntry& logEntry) override;
};
