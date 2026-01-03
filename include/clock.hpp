#pragma once

#include <cstdint>

namespace Profiler {

using time_stamp_ns = uint64_t;

class Clock {
public:
    // Returns monotonic timestamp in nanoseconds
    static time_stamp_ns Now();
};

} // namespace Profiler
