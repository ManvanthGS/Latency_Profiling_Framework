#pragma once

#include <cstdint>

#include "profiler/clock.hpp"

namespace Profiler {

class MetricSink; // forward declaration

class ScopedTimer {
public:
    explicit ScopedTimer(MetricSink& sink) noexcept;
    ~ScopedTimer() noexcept;

    // Non-copyable
    ScopedTimer(const ScopedTimer&) = delete;
    ScopedTimer& operator=(const ScopedTimer&) = delete;

    // Non-movable
    ScopedTimer(ScopedTimer&&) = delete;
    ScopedTimer& operator=(ScopedTimer&&) = delete;

private:
    MetricSink& sink_;
    TimestampNs start_time_ns;
};

} // namespace Profiler
