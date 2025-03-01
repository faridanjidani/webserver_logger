#include "ResultFormatter.hpp"

std::vector<std::pair<std::string, int>> ResultFormatter::getSortedHostAccess() const {
    std::vector<std::pair<std::string, int>> hostAccesses(
        statsCollector.getAllHostAccess().begin(), statsCollector.getAllHostAccess().end()
    );
    
    std::sort(hostAccesses.begin(), hostAccesses.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    return hostAccesses;
}

std::vector<std::pair<std::string, int>> ResultFormatter::getSortedSuccessfulURIAccess() const {
    std::vector<std::pair<std::string, int>> uriAccesses(
        statsCollector.getAllSuccessfulURIAccess().begin(), statsCollector.getAllSuccessfulURIAccess().end()
    );

    std::sort(uriAccesses.begin(), uriAccesses.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    return uriAccesses;
}

void ResultFormatter::printHostAccess(std::ostream& os, const std::vector<std::pair<std::string, int>>& hostAccesses) const {
    os << "Number of accesses per host (sorted):\n";
    for (const auto& [host, count] : hostAccesses) {
        os << host << " -> " << count << " accesses\n";
    }
}

void ResultFormatter::printSuccessfulURIAccess(std::ostream& os, const std::vector<std::pair<std::string, int>>& uriAccesses) const {
    os << "Successful Resource Accesses by URI (sorted):\n";
    for (const auto& [uri, count] : uriAccesses) {
        os << uri << " -> " << count << " times\n";
    }
}

void ResultFormatter::printSortedResults(std::ostream& os) const {
    auto hostAccesses = getSortedHostAccess();
    auto uriAccesses = getSortedSuccessfulURIAccess();

    printHostAccess(os, hostAccesses);
    os << "\n";
    printSuccessfulURIAccess(os, uriAccesses);
}