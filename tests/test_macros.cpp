#include <gtest/gtest.h>
#include "profiler/macros.hpp"
#include "profiler/metric_registry.hpp"

TEST(Macros, ProfilerScopeDoesNotCrash) {
    {
        PROFILER_SCOPE("MacroTest");
    }

    auto snapshot =
        Profiler::MetricRegistry::GetSink("MacroTest").Snapshot();

    EXPECT_EQ(snapshot.count, 1u);
}
