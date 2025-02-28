#include "gtest/gtest.h"
#include "StatsCollector.hpp"
#include "SuccessfulURICounter.hpp"
#include "HostAccessCounter.hpp"
#include <unordered_map>
#include <string>
#include <memory>


// A helper function to add log entries to the StatsCollector
void addLogEntriesToStatsCollector(StatsCollector& statsCollector, const std::vector<LogEntry>& logEntries) {
    for (const auto& entry : logEntries) {
        statsCollector.processLogEntry(entry);
    }
}

// Test for the StatsCollector class
TEST(StatsCollectorTest, MetricsProcessing) {
    // Create the StatsCollector instance
    StatsCollector statsCollector;

    // Add metrics (counter for successful URI accesses and host accesses)
    statsCollector.addMetric(std::make_unique<SuccessfulURICounter>(statsCollector));
    statsCollector.addMetric(std::make_unique<HostAccessCounter>(statsCollector));

    // Define log entries for the test
    std::vector<LogEntry> logEntries = {
        {"host1.com","[29:23:53:53]",  "GET", "/docs/Access", 200},
        {"host2.com","[29:23:53:53]",  "GET", "/home", 200},
        {"host1.com","[29:23:53:53]",  "GET", "/docs/Access", 200},
        {"host3.com","[29:23:53:53]",  "GET", "/about", 404},
        {"host1.com","[29:23:53:53]",  "POST","/docs/Access",  200},
        {"host2.com","[29:23:53:53]",  "GET", "/about", 200}
    };

    // Add log entries to the StatsCollector
    addLogEntriesToStatsCollector(statsCollector, logEntries);

    // Test the results in StatsCollector

    // Test successful URI access count for "/docs/Access"
    EXPECT_EQ(statsCollector.getSuccessfulURIAccessCount("/docs/Access"), 2);
    EXPECT_EQ(statsCollector.getSuccessfulURIAccessCount("/home"), 1);
    EXPECT_EQ(statsCollector.getSuccessfulURIAccessCount("/about"), 1);

    // Test host access counts
    EXPECT_EQ(statsCollector.getHostAccessCount("host1.com"), 3);
    EXPECT_EQ(statsCollector.getHostAccessCount("host2.com"), 2);
    EXPECT_EQ(statsCollector.getHostAccessCount("host3.com"), 1);

    // Test getAllSuccessfulURIAccess()
    auto uriAccessMap = statsCollector.getAllSuccessfulURIAccess();
    EXPECT_EQ(uriAccessMap["/docs/Access"], 2);
    EXPECT_EQ(uriAccessMap["/home"], 1);
    EXPECT_EQ(uriAccessMap["/about"], 1);

    // Test getAllHostAccess()
    auto hostAccessMap = statsCollector.getAllHostAccess();
    EXPECT_EQ(hostAccessMap["host1.com"], 3);
    EXPECT_EQ(hostAccessMap["host2.com"], 2);
    EXPECT_EQ(hostAccessMap["host3.com"], 1);
}
