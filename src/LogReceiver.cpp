#include "LogReceiver.hpp"
#include <fstream>
#include <iostream>

LogReceiver::LogReceiver(const std::string& source) : source(source) {}

void LogReceiver::setCallback(LogCallback callback) {
    logCallback = callback;
}

void LogReceiver::startReceiving() {
    processFile();
}

void LogReceiver::processFile() {
    std::ifstream file(source);
    if (!file) {
        std::cerr << "Error: Unable to open log file: " << source << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (logCallback) {
            logCallback(line); // Passes each log entry to the callback
        }
    }
}
