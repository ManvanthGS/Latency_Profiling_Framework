#include <gtest/gtest.h>
#include "profiler/metric_registry.hpp"

TEST(MetricRegistryTest, SameNameSameSink) {
    auto& a = Profiler::MetricRegistry::GetSink("A");
    auto& b = Profiler::MetricRegistry::GetSink("A");

    EXPECT_EQ(&a, &b);
}

TEST(MetricRegistryTest, DifferentNamesDifferentSinks) {
    auto& a = Profiler::MetricRegistry::GetSink("A");
    auto& b = Profiler::MetricRegistry::GetSink("B");

    EXPECT_NE(&a, &b);
}
