#pragma once
#include "StatsCollector.hpp"
#include <gmock/gmock.h>

class MockStatsCollector : public StatsCollector {
public:
    MOCK_CONST_METHOD0(getAllHostAccess, std::unordered_map<std::string, int>());
    MOCK_CONST_METHOD0(getAllSuccessfulURIAccess, std::unordered_map<std::string, int>());
};
