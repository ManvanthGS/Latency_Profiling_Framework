#pragma once

#include <cstdint>
#include <array>

namespace Profiler {

// V1 histogram bucket count
static constexpr uint32_t HISTOGRAM_BUCKET_COUNT = 8;

class LatencyHistogram {
public:
    LatencyHistogram() noexcept;

    void Add(uint64_t latency_ns) noexcept;

    // percentile in range [0.0, 100.0]
    uint64_t Percentile(double percentile) const noexcept;

    uint64_t Count() const noexcept;

private:
    uint32_t BucketIndex(uint64_t latency_ns) const noexcept;

private:
    std::array<uint64_t, HISTOGRAM_BUCKET_COUNT> buckets_;
    uint64_t total_count_;
};

} // namespace Profiler
