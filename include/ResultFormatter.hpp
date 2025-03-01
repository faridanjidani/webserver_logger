#pragma once
#include "StatsCollector.hpp"
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>

class ResultFormatter {
private:
    const StatsCollector& statsCollector;

public:
    explicit ResultFormatter(const StatsCollector& collector)
        : statsCollector(collector) {}

    std::vector<std::pair<std::string, int>> getSortedHostAccess() const;
    std::vector<std::pair<std::string, int>> getSortedSuccessfulURIAccess() const;

    void printSortedResults(std::ostream& os) const;
    private:
    void printHostAccess(std::ostream& os, const std::vector<std::pair<std::string, int>>& hostAccesses) const;
    void printSuccessfulURIAccess(std::ostream& os, const std::vector<std::pair<std::string, int>>& uriAccesses) const;
};
