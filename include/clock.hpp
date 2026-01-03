#pragma once

#include <cstdint>

namespace Profiler
{

using TimestampNs = uint64_t;

class Clock
{
  public:
    // Returns monotonic timestamp in nanoseconds
    static TimestampNs Now();
};

} // namespace Profiler
