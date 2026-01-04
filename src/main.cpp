#include "clock.hpp"
#include "scoped_timer.hpp"
#include "metric_sink.hpp"
#include "reporter.hpp"
#include <cassert>
#include <iostream>

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
        Profiler::MetricSink sink;
        {
            Profiler::ScopedTimer timer(sink);
            // Simulate some work
            for (int i = 0; i < 1000000; ++i);
        }

        Profiler::MetricSnapshot snapshot = sink.Snapshot();
        Profiler::Reporter::WriteHumanReadable(
                "ScopedTimer Test",
                snapshot,
                std::cout
            );
        // Profiler::Reporter::WriteCsvHeader(csv_file);
        // Profiler::Reporter::WriteCsvRow(
        //     "ScopedTimer Test",
        //     snapshot,
        //     csv_file
        // );
    }

    return 0;
}
