cmake_minimum_required(VERSION 3.14)
project(WebServerLogger)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)




# Add include directories
include_directories(include)
include_directories(src/metrics)
# Source files
set(SOURCES
    src/LogReceiver.cpp
    src/LogParser.cpp
    src/StatsCollector.cpp
    src/metrics/SuccessfulURICounter.cpp
    src/metrics/HostAccessCounter.cpp
    src/ResultFormatter.cpp
    src/main.cpp
)



# Enable testing
enable_testing()
add_subdirectory(tests)
# Create executable
add_executable(WebServerLogger ${SOURCES})

