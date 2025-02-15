cmake_minimum_required(VERSION 3.14)
project(TrackAnalyzer)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)

# Add main executable
add_executable(TrackAnalyzer
    src/trackAnalyzer.cpp
    src/main.cpp
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})