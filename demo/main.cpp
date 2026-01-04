#include "profiler/clock.hpp"
#include "profiler/scoped_timer.hpp"
#include "profiler/metric_sink.hpp"
#include "profiler/reporter.hpp"
#include "profiler/macros.hpp"
#include <cassert>
#include <iostream>
#include <fstream>

int main()
{
    Profiler::TimestampNs timestamp = Profiler::Clock::Now();
    std::cout << "Current monotonic timestamp (ns): " << timestamp << std::endl;

    auto t1 = Profiler::Clock::Now();
    auto t2 = Profiler::Clock::Now();
    assert(t2 >= t1);

    std::cout << "Time difference between two calls (ns): " << (t2 - t1) << std::endl;

    // Test scoped timer
    {
        {
            PROFILER_SCOPE("Test Metric");
            // Simulate some work
            for (int i = 0; i < 1000000; ++i);
        }

        Profiler::MetricRegistry::DumpAll(std::cout);

        std::ofstream csv("latency.csv");
        Profiler::MetricRegistry::DumpAllCsv(csv);
    }

    return 0;
}
