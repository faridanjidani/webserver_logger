cmake_minimum_required(VERSION 3.10)
project(WebServerLoggerTests)



# GoogleTest Setup
add_subdirectory(${CMAKE_SOURCE_DIR}/extern/googletest extern/googletest)
include_directories(${CMAKE_SOURCE_DIR}/extern/googletest/googlemock/include/)
include_directories(${CMAKE_SOURCE_DIR}/extern/googletest/include)
# Add test executables
add_executable(test_LogReceiver test_LogReceiver.cpp ../src/LogReceiver.cpp)
add_executable(test_LogParser test_LogParser.cpp ../src/LogParser.cpp)
add_executable(test_StatsCollector test_StatsCollector.cpp ../src/StatsCollector.cpp ../src/metrics/SuccessfulURICounter.cpp ../src/metrics/HostAccessCounter.cpp)
add_executable(test_ResultFormatter test_ResultFormatter.cpp ../src/ResultFormatter.cpp ../src/StatsCollector.cpp ../src/metrics/SuccessfulURICounter.cpp ../src/metrics/HostAccessCounter.cpp)
add_executable(test_Integration test_Integration.cpp ../src/LogReceiver.cpp ../src/LogParser.cpp ../src/StatsCollector.cpp ../src/metrics/SuccessfulURICounter.cpp ../src/metrics/HostAccessCounter.cpp ../src/ResultFormatter.cpp)
# Link GoogleTest
target_link_libraries(test_LogReceiver PRIVATE GTest::gtest GTest::gtest_main)
target_link_libraries(test_LogParser PRIVATE GTest::gtest GTest::gtest_main)
target_link_libraries(test_StatsCollector PRIVATE GTest::gtest GTest::gtest_main)
target_link_libraries(test_ResultFormatter PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main) 
target_link_libraries(test_Integration PRIVATE GTest::gtest GTest::gtest_main)
# Register the test
add_test(NAME LogReceiverTest COMMAND test_LogReceiver)
add_test(NAME LogParserTest COMMAND test_LogParser)
add_test(NAME StatsCollectorTest COMMAND test_StatsCollector)
add_test(NAME ResultFormatterTest COMMAND test_ResultFormatter)
add_test(NAME IntegrationTest COMMAND test_Integration)



