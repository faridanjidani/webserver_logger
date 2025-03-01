#include "LogParser.hpp"
#include "StatsCollector.hpp"
#include "ResultFormatter.hpp"
#include "LogReceiver.hpp"
#include "SuccessfulURICounter.hpp"
#include "HostAccessCounter.hpp"
#include <gtest/gtest.h>
#include <sstream>
// Helper function to create a temporary test log file
void createTestLogFile(const std::string& filename, const std::vector<std::string>& logEntries) {
    std::ofstream file(filename);
    for (const auto& entry : logEntries) {
        file << entry << "\n";
    }
    file.close();
}

TEST(IntegrationTest, ProcessLogAndGenerateSortedOutputAccess) {
    // Simulate log entries
    const std::string testFile = "test_logIntegration.txt";
    std::vector<std::string> input_raw_data = {
        "141.243.1.172 [29:23:53:25] \"GET /Software.html HTTP/1.0\" 200 1497",
        "query2.lycos.cs.cmu.edu [29:23:53:36] \"GET /Consumer.html HTTP/1.0\" 200 1325",
        "tanuki.twics.com [29:23:53:53] \"GET /News.html HTTP/1.0\" 200 1014",
        "wpbfl2-45.gate.net [29:23:54:15] \"GET / HTTP/1.0\" 200 4889",
        "wpbfl2-45.gate.net [29:23:54:16] \"GET /icons/circle_logo_small.gif HTTP/1.0\" 200 2624",
        "wpbfl2-45.gate.net [29:23:54:18] \"GET /logos/small_gopher.gif HTTP/1.0\" 200 935",
        "140.112.68.165 [29:23:54:19] \"GET /logos/us-flag.gif HTTP/1.0\" 200 2788",
        "wpbfl2-45.gate.net [29:23:54:19] \"GET /logos/small_ftp.gif HTTP/1.0\" 200 124",
        "wpbfl2-45.gate.net [29:23:54:19] \"GET /icons/book.gif HTTP/1.0\" 200 156",
        "wpbfl2-45.gate.net [29:23:54:19] \"GET /logos/us-flag.gif HTTP/1.0\" 200 2788",
        "tanuki.twics.com [29:23:54:19] \"GET /docs/OSWRCRA/general/hotline HTTP/1.0\" 302 -",
        "wpbfl2-45.gate.net [29:23:54:20] \"GET /icons/ok2-0.gif HTTP/1.0\" 200 231",
        "tanuki.twics.com [29:23:54:25] \"GET /OSWRCRA/general/hotline/ HTTP/1.0\" 200 991",
        "tanuki.twics.com [29:23:54:37] \"GET /docs/OSWRCRA/general/hotline/95report HTTP/1.0\" 302 -",
        "wpbfl2-45.gate.net [29:23:54:37] \"GET /docs/browner/adminbio.html HTTP/1.0\" 200 4217",
        "tanuki.twics.com [29:23:54:40] \"GET /OSWRCRA/general/hotline/95report/ HTTP/1.0\" 200 1250",
        "wpbfl2-45.gate.net [29:23:55:01] \"GET /docs/browner/cbpress.gif HTTP/1.0\" 200 51661",
        "dd15-032.compuserve.com [29:23:55:21] \"GET /Access/chapter1/s2-4.html HTTP/1.0\" 200 4602",
        "tanuki.twics.com [29:23:55:23] \"GET /docs/OSWRCRA/general/hotline/95report/05_95mhr.txt.html HTTP/1.0\" 200 56431",
        "wpbfl2-45.gate.net [29:23:55:29] \"GET /docs/Access HTTP/1.0\" 302 -",
        "140.112.68.165 [29:23:55:33] \"GET /logos/us-flag.gif HTTP/1.0\" 200 2788",
        "wpbfl2-45.gate.net [29:23:55:46] \"GET /information.html HTTP/1.0\" 200 617",
        "wpbfl2-45.gate.net [29:23:55:47] \"GET /icons/people.gif HTTP/1.0\" 200 224",
        "wpbfl2-45.gate.net [29:23:56:03] \"GET /docs/Access HTTP/1.0\" 302 -",
        "wpbfl2-45.gate.net [29:23:56:12] \"GET /Access/ HTTP/1.0\" 200 2376",
        "wpbfl2-45.gate.net [29:23:56:14] \"GET /Access/images/epaseal.gif HTTP/1.0\" 200 2624",
        "tanuki.twics.com [29:23:56:24] \"GET /OSWRCRA/general/hotline/95report/ HTTP/1.0\" 200 1250",
        "freenet2.carleton.ca [29:23:56:36] \"GET /emap/html/regions/four/ HTTP/1.0\" 200 15173",
        "wpbfl2-45.gate.net [29:23:57:05] \"GET /waisicons/unknown.gif HTTP/1.0\" 200 83",
        "ix-mia5-17.ix.netcom.com [29:23:57:06] \"GET /OWOW/ HTTP/1.0\" 200 1501",
        "wpbfl2-45.gate.net [29:23:57:08] \"POST /cgi-bin/waisgate/134.67.99.11=earth1.epa.gov=210=/indexes/ACCESS=gopher%40earth1.epa.gov=0.00=:free HTTP/1.0\" 200 26217",
        "wpbfl2-45.gate.net [29:23:57:12] \"GET /waisicons/text.xbm HTTP/1.0\" 200 527",
        "ix-knx-tn1-22.ix.netcom.com [29:23:57:28] \"GET / HTTP/1.0\" 200 4889",
        "hmu4.cs.auckland.ac.nz [29:23:57:35] \"GET /docs/GCDOAR/EnergyStar.html HTTP/1.0\" 200 6829",
        "ix-knx-tn1-22.ix.netcom.com [29:23:57:38] \"GET /icons/circle_logo_small.gif HTTP/1.0\" 200 2624",
        "suburbia.apana.org.au [29:23:57:39] \"GET /docs/PressReleases/1995/August/Day-22 HTTP/1.0\" 302 -",
        "hmu4.cs.auckland.ac.nz [29:23:57:39] \"GET /docs/GCDOAR/gifs/estarcsm.gif HTTP/1.0\" 200 7005",
        "hmu4.cs.auckland.ac.nz [29:23:57:40] \"GET /docs/GCDOAR/gifs/gl.gif HTTP/1.0\" 200 3302"
    };
          
    // Define expected input data
    std::set<std::pair<std::string, int>>  hostAccessData = {
        {"wpbfl2-45.gate.net", 18},
        {"tanuki.twics.com", 7},
        {"hmu4.cs.auckland.ac.nz", 3},
        {"140.112.68.165", 2},
        {"ix-knx-tn1-22.ix.netcom.com", 2},
        {"141.243.1.172", 1},
        {"query2.lycos.cs.cmu.edu", 1},
        {"dd15-032.compuserve.com", 1},
        {"freenet2.carleton.ca", 1},
        {"ix-mia5-17.ix.netcom.com", 1},
        {"suburbia.apana.org.au", 1}
    };

    createTestLogFile(testFile, input_raw_data);
    LogReceiver logReceiver(testFile);
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
    auto sortedOutputAccess = resultFormatter.getSortedHostAccess();
    std::set<std::pair<std::string, int>> setAccess(sortedOutputAccess.begin(), sortedOutputAccess.end());
    // Step 4: Compare results
    EXPECT_EQ(setAccess, hostAccessData);
}


TEST(IntegrationTest, ProcessLogAndGenerateSortedOutputURI) {
    // Simulate log entries
    const std::string testFile = "test_logIntegration.txt";
    std::vector<std::string> input_raw_data = {
        "141.243.1.172 [29:23:53:25] \"GET /Software.html HTTP/1.0\" 200 1497",
        "query2.lycos.cs.cmu.edu [29:23:53:36] \"GET /Consumer.html HTTP/1.0\" 200 1325",
        "tanuki.twics.com [29:23:53:53] \"GET /News.html HTTP/1.0\" 200 1014",
        "wpbfl2-45.gate.net [29:23:54:15] \"GET / HTTP/1.0\" 200 4889",
        "wpbfl2-45.gate.net [29:23:54:16] \"GET /icons/circle_logo_small.gif HTTP/1.0\" 200 2624",
        "wpbfl2-45.gate.net [29:23:54:18] \"GET /logos/small_gopher.gif HTTP/1.0\" 200 935",
        "140.112.68.165 [29:23:54:19] \"GET /logos/us-flag.gif HTTP/1.0\" 200 2788",
        "wpbfl2-45.gate.net [29:23:54:19] \"GET /logos/small_ftp.gif HTTP/1.0\" 200 124",
        "wpbfl2-45.gate.net [29:23:54:19] \"GET /icons/book.gif HTTP/1.0\" 200 156",
        "wpbfl2-45.gate.net [29:23:54:19] \"GET /logos/us-flag.gif HTTP/1.0\" 200 2788",
        "tanuki.twics.com [29:23:54:19] \"GET /docs/OSWRCRA/general/hotline HTTP/1.0\" 302 -",
        "wpbfl2-45.gate.net [29:23:54:20] \"GET /icons/ok2-0.gif HTTP/1.0\" 200 231",
        "tanuki.twics.com [29:23:54:25] \"GET /OSWRCRA/general/hotline/ HTTP/1.0\" 200 991",
        "tanuki.twics.com [29:23:54:37] \"GET /docs/OSWRCRA/general/hotline/95report HTTP/1.0\" 302 -",
        "wpbfl2-45.gate.net [29:23:54:37] \"GET /docs/browner/adminbio.html HTTP/1.0\" 200 4217",
        "tanuki.twics.com [29:23:54:40] \"GET /OSWRCRA/general/hotline/95report/ HTTP/1.0\" 200 1250",
        "wpbfl2-45.gate.net [29:23:55:01] \"GET /docs/browner/cbpress.gif HTTP/1.0\" 200 51661",
        "dd15-032.compuserve.com [29:23:55:21] \"GET /Access/chapter1/s2-4.html HTTP/1.0\" 200 4602",
        "tanuki.twics.com [29:23:55:23] \"GET /docs/OSWRCRA/general/hotline/95report/05_95mhr.txt.html HTTP/1.0\" 200 56431",
        "wpbfl2-45.gate.net [29:23:55:29] \"GET /docs/Access HTTP/1.0\" 302 -",
        "140.112.68.165 [29:23:55:33] \"GET /logos/us-flag.gif HTTP/1.0\" 200 2788",
        "wpbfl2-45.gate.net [29:23:55:46] \"GET /information.html HTTP/1.0\" 200 617",
        "wpbfl2-45.gate.net [29:23:55:47] \"GET /icons/people.gif HTTP/1.0\" 200 224",
        "wpbfl2-45.gate.net [29:23:56:03] \"GET /docs/Access HTTP/1.0\" 302 -",
        "wpbfl2-45.gate.net [29:23:56:12] \"GET /Access/ HTTP/1.0\" 200 2376",
        "wpbfl2-45.gate.net [29:23:56:14] \"GET /Access/images/epaseal.gif HTTP/1.0\" 200 2624",
        "tanuki.twics.com [29:23:56:24] \"GET /OSWRCRA/general/hotline/95report/ HTTP/1.0\" 200 1250",
        "freenet2.carleton.ca [29:23:56:36] \"GET /emap/html/regions/four/ HTTP/1.0\" 200 15173",
        "wpbfl2-45.gate.net [29:23:57:05] \"GET /waisicons/unknown.gif HTTP/1.0\" 200 83",
        "ix-mia5-17.ix.netcom.com [29:23:57:06] \"GET /OWOW/ HTTP/1.0\" 200 1501",
        "wpbfl2-45.gate.net [29:23:57:08] \"POST /cgi-bin/waisgate/134.67.99.11=earth1.epa.gov=210=/indexes/ACCESS=gopher%40earth1.epa.gov=0.00=:free HTTP/1.0\" 200 26217",
        "wpbfl2-45.gate.net [29:23:57:12] \"GET /waisicons/text.xbm HTTP/1.0\" 200 527",
        "ix-knx-tn1-22.ix.netcom.com [29:23:57:28] \"GET / HTTP/1.0\" 200 4889",
        "hmu4.cs.auckland.ac.nz [29:23:57:35] \"GET /docs/GCDOAR/EnergyStar.html HTTP/1.0\" 200 6829",
        "ix-knx-tn1-22.ix.netcom.com [29:23:57:38] \"GET /icons/circle_logo_small.gif HTTP/1.0\" 200 2624",
        "suburbia.apana.org.au [29:23:57:39] \"GET /docs/PressReleases/1995/August/Day-22 HTTP/1.0\" 302 -",
        "hmu4.cs.auckland.ac.nz [29:23:57:39] \"GET /docs/GCDOAR/gifs/estarcsm.gif HTTP/1.0\" 200 7005",
        "hmu4.cs.auckland.ac.nz [29:23:57:40] \"GET /docs/GCDOAR/gifs/gl.gif HTTP/1.0\" 200 3302"
    };
          
    std::set<std::pair<std::string, int>>  uriAccessData = {
        {"/logos/us-flag.gif", 3},
        {"/Software.html", 1},
        {"/Consumer.html", 1},
        {"/News.html", 1},
        {"/", 2},
        {"/icons/circle_logo_small.gif", 2},
        {"/icons/book.gif", 1},
        {"/logos/small_ftp.gif", 1},
        {"/icons/ok2-0.gif", 1},
        {"/OSWRCRA/general/hotline/", 1},
        {"/docs/browner/adminbio.html", 1},
        {"/docs/browner/cbpress.gif", 1},
        {"/Access/chapter1/s2-4.html", 1},
        {"/OSWRCRA/general/hotline/95report/", 2},
        {"/information.html", 1},
        {"/icons/people.gif", 1},
        {"/Access/", 1},
        {"/Access/images/epaseal.gif", 1},
        {"/emap/html/regions/four/", 1},
        {"/waisicons/unknown.gif", 1},
        {"/OWOW/", 1},
        {"/waisicons/text.xbm", 1},
        {"/docs/GCDOAR/EnergyStar.html", 1},
        {"/docs/GCDOAR/gifs/estarcsm.gif", 1},
        {"/docs/OSWRCRA/general/hotline/95report/05_95mhr.txt.html", 1},
        {"/logos/small_gopher.gif", 1},
        {"/docs/GCDOAR/gifs/gl.gif", 1}
    };
    createTestLogFile(testFile, input_raw_data);
    LogReceiver logReceiver(testFile);
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
    auto sortedOutputURI = resultFormatter.getSortedSuccessfulURIAccess();
    std::set<std::pair<std::string, int>> setURI(sortedOutputURI.begin(), sortedOutputURI.end());
    // Step 4: Compare results
    EXPECT_EQ(setURI, uriAccessData);
}
