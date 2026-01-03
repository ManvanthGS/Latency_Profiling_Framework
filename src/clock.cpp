#include "clock.hpp"

#include <chrono>

namespace Profiler
{

TimestampNs Clock::Now()
{
    using namespace std::chrono;
    return duration_cast<nanoseconds>(steady_clock::now().time_since_epoch()).count();
}

} // namespace Profiler
