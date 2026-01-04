#pragma once

#include "scoped_timer.hpp"
#include "metric_registry.hpp"

// Compile-time switch
#ifdef PROFILER_ENABLE

#define PROFILER_SCOPE(metric_name) \
    Profiler::ScopedTimer profiler_scoped_timer( \
        Profiler::MetricRegistry::GetSink(metric_name))

#else

#define PROFILER_SCOPE(metric_name) \
    do { } while (0)

#endif
