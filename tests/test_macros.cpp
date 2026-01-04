#include <gtest/gtest.h>
#include "profiler/macros.hpp"
#include "profiler/metric_registry.hpp"

TEST(MacroTest, ProfilerScopeRecords) {
    {
        PROFILER_SCOPE("Macro::Test");
    }

    auto snapshot =
        Profiler::MetricRegistry::GetSink("Macro::Test").Snapshot();

    EXPECT_EQ(snapshot.count, 1u);
}
