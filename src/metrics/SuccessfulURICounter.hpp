#pragma once

#include "IMetric.hpp"
#include <unordered_map>
#include <string>

class SuccessfulURICounter : public IMetric {
public:
    using IMetric::IMetric;  // Inherit constructor
    void processEntry(const LogEntry& entry) override;
};
