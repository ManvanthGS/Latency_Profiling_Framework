#include <gtest/gtest.h>
#include "profiler/scoped_timer.hpp"
#include "profiler/metric_sink.hpp"

TEST(ScopedTimer, RecordsExactlyOnce) {
    Profiler::MetricSink sink;

    {
        Profiler::ScopedTimer timer(sink);
    }

    auto snapshot = sink.Snapshot();
    EXPECT_EQ(snapshot.count, 1u);
}

TEST(ScopedTimerTest, WorksWithEarlyReturn) {
    Profiler::MetricSink sink;

    auto func = [&]() {
        Profiler::ScopedTimer timer(sink);
        return;
    };

    func();

    auto snapshot = sink.Snapshot();
    EXPECT_EQ(snapshot.count, 1u);
}
