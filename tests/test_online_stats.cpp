#include <gtest/gtest.h>
#include "profiler/online_stats.hpp"

TEST(OnlineStatsTest, BasicStatistics) {
    Profiler::OnlineStats stats;

    stats.Add(100);
    stats.Add(200);
    stats.Add(300);

    EXPECT_EQ(stats.Count(), 3u);
    EXPECT_EQ(stats.Min(), 100u);
    EXPECT_EQ(stats.Max(), 300u);
    EXPECT_NEAR(stats.Mean(), 200.0, 1e-6);
}

TEST(OnlineStatsTest, VarianceNonNegative) {
    Profiler::OnlineStats stats;
    stats.Add(100);
    stats.Add(200);

    EXPECT_GE(stats.Variance(), 0.0);
}
