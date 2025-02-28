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
// TEST(ResultFormatterTest, SortsSuccessfulURIAccessCorrectly) {
//     MockStatsCollector mockStats;

//     // Unsorted input data
//     std::unordered_map<std::string, int> uriAccessData = {
//         {"/home", 3},
//         {"/about", 7},
//         {"/docs", 2}
//     };

//     // Expect function to be called once and return our data
//     EXPECT_CALL(mockStats, getAllSuccessfulURIAccess()).WillOnce(Return(uriAccessData));

//     ResultFormatter formatter(mockStats);
    
//     // Get sorted results
//     auto sortedOutput = formatter.getSortedSuccessfulURIAccess();

//     // Expected sorted output
//     std::vector<std::pair<std::string, int>> expectedOutput = {
//         {"/about", 7},
//         {"/home", 3},
//         {"/docs", 2}
//     };

//     // Check if the sorted result matches expected order
//     EXPECT_EQ(sortedOutput, expectedOutput);
// }


// TEST(ResultFormatterTest, SaveToFile) {
//     MockStatsCollector mockStats;

//     std::unordered_map<std::string, int> hostAccessData = {
//         {"host1.com", 3},
//         {"host2.com", 2},
//         {"host3.com", 1}
//     };
//     std::unordered_map<std::string, int> uriAccessData = {
//         {"/docs/Access", 2},
//         {"/home", 1},
//         {"/about", 1}
//     };

//     EXPECT_CALL(mockStats, getAllHostAccess()).WillOnce(Return(hostAccessData));
//     EXPECT_CALL(mockStats, getAllSuccessfulURIAccess()).WillOnce(Return(uriAccessData));

//     ResultFormatter formatter;
//     std::string filename = "test_output.txt";
//     formatter.saveResultsToFile(mockStats, filename);

//     // Read the file to verify
//     std::ifstream file(filename);
//     std::stringstream buffer;
//     buffer << file.rdbuf();
//     file.close();

//     std::string expectedOutput =
//         "Host Access Counts:\n"
//         "host1.com -> 3 times\n"
//         "host2.com -> 2 times\n"
//         "host3.com -> 1 times\n"
//         "\nSuccessful Resource Accesses by URI:\n"
//         "/docs/Access -> 2 times\n"
//         "/home -> 1 times\n"
//         "/about -> 1 times\n";

//     EXPECT_EQ(buffer.str(), expectedOutput);
// }
