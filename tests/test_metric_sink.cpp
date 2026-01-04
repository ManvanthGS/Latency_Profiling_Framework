#include <gtest/gtest.h>
#include "profiler/metric_sink.hpp"

TEST(MetricSinkTest, RecordsMultipleSamples) {
    Profiler::MetricSink sink;

    sink.Record(100);
    sink.Record(200);
    sink.Record(300);

    auto snapshot = sink.Snapshot();
    EXPECT_EQ(snapshot.count, 3u);
    EXPECT_EQ(snapshot.min_ns, 100u);
    EXPECT_EQ(snapshot.max_ns, 300u);
}

TEST(MetricSinkTest, SnapshotIsConsistent) {
    Profiler::MetricSink sink;

    for (int i = 0; i < 100; ++i)
        sink.Record(150);

    auto snapshot1 = sink.Snapshot();
    auto snapshot2 = sink.Snapshot();

    EXPECT_EQ(snapshot1.count, snapshot2.count);
    EXPECT_EQ(snapshot1.min_ns, snapshot2.min_ns);
    EXPECT_EQ(snapshot1.max_ns, snapshot2.max_ns);
    EXPECT_EQ(snapshot1.mean_ns, snapshot2.mean_ns);
}
