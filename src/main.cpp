#include "clock.hpp"
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

    return 0;
}
