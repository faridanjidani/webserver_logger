#include "LogReceiver.hpp"
#include <gtest/gtest.h>
#include <fstream>
#include <vector>

// Helper function to create a temporary test log file
void createTestLogFile(const std::string& filename, const std::vector<std::string>& logEntries) {
    std::ofstream file(filename);
    for (const auto& entry : logEntries) {
        file << entry << "\n";
    }
    file.close();
}

// Test LogReceiver with a sample log file
TEST(LogReceiverTest, ReadsLogFileCorrectly) {
    // Prepare test log file
    const std::string testFile = "test_logReceiver.txt";
    std::vector<std::string> expectedLogs = {
        "141.243.1.172 [29:23:53:25] \"GET /Software.html HTTP/1.0\" 200 1497",
        "query2.lycos.cs.cmu.edu [29:23:53:36] \"GET /Consumer.html HTTP/1.0\" 200 1325",
        "tanuki.twics.com [29:23:53:53] \"GET /News.html HTTP/1.0\" 200 1014",
        "wpbfl2-45.gate.net [29:23:54:15] \"GET / HTTP/1.0\" 200 4889"
    };
    createTestLogFile(testFile, expectedLogs);

    // Capture received logs
    std::vector<std::string> receivedLogs;
    
    // Create LogReceiver instance and set callback
    LogReceiver receiver(testFile);
    receiver.setCallback([&receivedLogs](const std::string& logEntry) {
        receivedLogs.push_back(logEntry);
    });

    // Start receiving logs
    receiver.startReceiving();

    // Verify logs match expected values
    ASSERT_EQ(receivedLogs.size(), expectedLogs.size());
    for (size_t i = 0; i < expectedLogs.size(); ++i) {
        EXPECT_EQ(receivedLogs[i], expectedLogs[i]);
    }
}
