#include "LogParser.hpp"
#include <gtest/gtest.h>

// Test valid log parsing
TEST(LogParserTest, ParsesValidLog) {
    std::string log = "wpbfl2-45.gate.net [29:23:55:29] \"GET /docs/Access HTTP/1.0\" 302 -";
    auto parsedEntry = LogParser::parseLogEntry(log);

    ASSERT_TRUE(parsedEntry.has_value());
    EXPECT_EQ(parsedEntry->host, "wpbfl2-45.gate.net");
    EXPECT_EQ(parsedEntry->timestamp, "2024-08-29 23:55:29");
    EXPECT_EQ(parsedEntry->method, "GET");
    EXPECT_EQ(parsedEntry->uri, "/docs/Access");
    EXPECT_EQ(parsedEntry->statusCode, 302);
}

// Test invalid log format
TEST(LogParserTest, FailsOnInvalidLog) {
    std::string invalidLog = "Invalid log format example";
    auto parsedEntry = LogParser::parseLogEntry(invalidLog);
    
    EXPECT_FALSE(parsedEntry.has_value());
}

// Test different HTTP methods
TEST(LogParserTest, ParsesDifferentMethods) {
    std::string log = "example.com [12:34:56:78] \"POST /api/login HTTP/1.1\" 200 -";
    auto parsedEntry = LogParser::parseLogEntry(log);

    ASSERT_TRUE(parsedEntry.has_value());
    EXPECT_EQ(parsedEntry->method, "POST");
    EXPECT_EQ(parsedEntry->uri, "/api/login");
    EXPECT_EQ(parsedEntry->statusCode, 200);
}

// Test missing fields
TEST(LogParserTest, FailsOnIncompleteLog) {
    std::string log = "missing-fields.com [12:34:56:78] \"GET\"";
    auto parsedEntry = LogParser::parseLogEntry(log);

    EXPECT_FALSE(parsedEntry.has_value());
}
