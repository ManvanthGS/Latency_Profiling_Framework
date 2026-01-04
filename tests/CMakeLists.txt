include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(profiler_tests
    test_scoped_timer.cpp
    test_online_stats.cpp
    test_latency_histogram.cpp
    test_metric_registry.cpp
    test_macros.cpp
)

target_link_libraries(profiler_tests
    PRIVATE
        profiler
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(profiler_tests)
