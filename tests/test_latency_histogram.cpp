#include <gtest/gtest.h>
#include "profiler/latency_histogram.hpp"

TEST(LatencyHistogram, PercentilesMonotonic) {
    Profiler::LatencyHistogram hist;

    for (int i = 0; i < 1000; ++i)
        hist.Add(1000 + i);

    auto p50 = hist.Percentile(50.0);
    auto p95 = hist.Percentile(95.0);
    auto p99 = hist.Percentile(99.0);

    EXPECT_LE(p50, p95);
    EXPECT_LE(p95, p99);
}
