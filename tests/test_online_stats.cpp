#include <gtest/gtest.h>
#include "profiler/online_stats.hpp"

TEST(OnlineStats, MeanMinMaxCorrect) {
    Profiler::OnlineStats stats;
    stats.Add(10);
    stats.Add(20);
    stats.Add(30);

    EXPECT_EQ(stats.Count(), 3u);
    EXPECT_EQ(stats.Min(), 10u);
    EXPECT_EQ(stats.Max(), 30u);
    EXPECT_NEAR(stats.Mean(), 20.0, 1e-6);
}
