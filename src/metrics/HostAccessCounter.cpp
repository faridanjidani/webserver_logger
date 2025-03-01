// HostAccessCounter.cpp
#include "HostAccessCounter.hpp"
#include <sstream>

void HostAccessCounter::processEntry(const LogEntry& logEntry) {
    statsCollector.incrementHostAccess(logEntry.host);
}
