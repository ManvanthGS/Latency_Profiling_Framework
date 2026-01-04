cmake_minimum_required(VERSION 3.16)
project(Latency_Profiling_Framework LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Recurse .cpp and .hpp files
file(GLOB_RECURSE CPP_SOURCES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE HPP_SOURCES CONFIGURE_DEPENDS include/*.hpp)

# Add executable
add_executable(profiling_framework ${CPP_SOURCES} ${HPP_SOURCES})
target_include_directories(profiling_framework PRIVATE include)

# Define PROFILER_ENABLE for the target
target_compile_definitions(profiling_framework PRIVATE PROFILER_ENABLE)

# Enable Test Framework
enable_testing()
