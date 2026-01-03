#include "scoped_timer.hpp"
#include "metric_sink.hpp"

namespace Profiler {

ScopedTimer::ScopedTimer(MetricSink& sink) noexcept
    : sink_(sink),
      start_time_ns(Clock::Now()) {}

ScopedTimer::~ScopedTimer() noexcept {
    const TimestampNs end_time_ns = Clock::Now();
    const TimestampNs elapsed_ns = end_time_ns - start_time_ns;
    // sink_.Record(elapsed_ns);
}

} // namespace Profiler
