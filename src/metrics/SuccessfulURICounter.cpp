#include "SuccessfulURICounter.hpp"
#include <iostream>

void SuccessfulURICounter::processEntry(const LogEntry& entry) {
    if (entry.statusCode == 200 && entry.method == "GET") {
        statsCollector.incrementSuccessfulURIAccess(entry.uri);
    }
}

