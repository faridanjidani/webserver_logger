#include <gtest/gtest.h>
#include "gmock/gmock.h"
#include "ResultFormatter.hpp"
#include "MockStatsCollector.hpp"
#include <sstream>
#include <fstream>

using ::testing::Return;

TEST(ResultFormatterTest, SortsHostAccessCorrectly) {
    MockStatsCollector mockStats;

    // Unsorted input data
    std::unordered_map<std::string, int> hostAccessData = {
        {"hostA", 5},
        {"hostB", 10},
        {"hostC", 2}
    };

    // Mock the function call
    EXPECT_CALL(mockStats, getAllHostAccess()).WillOnce(Return(hostAccessData));
    // Create formatter and get sorted output
    ResultFormatter formatter(mockStats);
    auto sortedOutput = formatter.getSortedHostAccess();

    // Expected sorted output
    std::vector<std::pair<std::string, int>> expectedOutput = {
        {"hostB", 10},
        {"hostA", 5},
        {"hostC", 2}
    };

    // Check if the sorted result matches expected order
    EXPECT_EQ(sortedOutput, expectedOutput);
}