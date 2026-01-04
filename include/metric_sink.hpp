#pragma once

#include <cstdint>
#include <mutex>

#include "latency_histogram.hpp"
#include "online_stats.hpp"

namespace Profiler
{

struct MetricSnapshot
{
    uint64_t count;
    double mean_ns;
    double variance_ns;
    uint64_t min_ns;
    uint64_t max_ns;
    uint64_t p50_ns;
    uint64_t p95_ns;
    uint64_t p99_ns;
};

class MetricSink
{
  public:
    MetricSink() noexcept;

    void Record(uint64_t latency_ns) noexcept;
    MetricSnapshot Snapshot() const noexcept;

  private:
    mutable std::mutex mutex_;
    OnlineStats stats_;
    LatencyHistogram histogram_;
};

} // namespace Profiler
