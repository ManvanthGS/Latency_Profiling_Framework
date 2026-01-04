cmake_minimum_required(VERSION 3.20)
project(profiler LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(PROFILER_ENABLE "Enable profiling" ON)

add_library(profiler STATIC
    src/clock.cpp
    src/scoped_timer.cpp
    src/online_stats.cpp
    src/latency_histogram.cpp
    src/metric_sink.cpp
    src/metric_registry.cpp
    src/reporter.cpp
)

target_include_directories(profiler
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(PROFILER_ENABLE)
    target_compile_definitions(profiler PUBLIC PROFILER_ENABLE)
endif()

add_subdirectory(tests)
add_subdirectory(benchmarks)
add_subdirectory(demo)
