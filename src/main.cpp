

#include "LogParser.hpp"
#include "LogReceiver.hpp"
#include "StatsCollector.hpp"
#include "HostAccessCounter.hpp"
#include "SuccessfulURICounter.hpp"
#include "ResultFormatter.hpp"
#include <iostream>
#include <fstream>
int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <log_file_path>\n";
        return 1;
    }
    std::string logFilePath = argv[1];
    LogReceiver logReceiver(logFilePath);

    // Initialize StatsCollector
    StatsCollector statsCollector;
    // Add Metrics
    statsCollector.addMetric(std::make_unique<SuccessfulURICounter>(statsCollector));
    statsCollector.addMetric(std::make_unique<HostAccessCounter>(statsCollector));
    ResultFormatter resultFormatter(statsCollector);
    logReceiver.setCallback([&statsCollector](const std::string& logEntry) {
        auto parsedEntry = LogParser::parseLogEntry(logEntry);
        if (parsedEntry.has_value()) {
            statsCollector.processLogEntry(parsedEntry.value());
        }


    });

    logReceiver.startReceiving();
    resultFormatter.printSortedResults(std::cout);
    return 0;
}