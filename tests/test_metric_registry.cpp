#include <gtest/gtest.h>
#include "profiler/metric_registry.hpp"

TEST(MetricRegistry, SameNameSameSink) {
    auto& a = Profiler::MetricRegistry::GetSink("X");
    auto& b = Profiler::MetricRegistry::GetSink("X");

    EXPECT_EQ(&a, &b);
}
