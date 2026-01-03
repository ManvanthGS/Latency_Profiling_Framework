cmake_minimum_required(VERSION 3.16)
project(Latency_Profiling_Framework LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Library Sources (Adding sources manually for readability)
set(PROJECT_SOURCES
    #sources
    src/main.cpp
    src/clock.cpp

    #includes
    include/clock.hpp
)

# Add executable
add_executable(profiling_framework ${PROJECT_SOURCES})
target_include_directories(profiling_framework PRIVATE include)

# Enable Test Framework
enable_testing()
