#include "clock.hpp"
#include "scoped_timer.hpp"
#include "metric_sink.hpp"
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
            for (volatile int i = 0; i < 1000000; ++i);
        }
        Profiler::MetricSnapshot snapshot = sink.Snapshot();
        std::cout << "Recorded " << snapshot.count << " measurements." << std::endl;
        std::cout << "Mean latency (ns): " << snapshot.mean_ns << std::endl;
    }

    return 0;
}
