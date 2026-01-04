#include "profiler/latency_histogram.hpp"

namespace Profiler {

LatencyHistogram::LatencyHistogram() noexcept
    : buckets_{}, total_count_(0) {}

void LatencyHistogram::Add(uint64_t latency_ns) noexcept {
    const uint32_t index = BucketIndex(latency_ns);
    ++buckets_[index];
    ++total_count_;
}

uint64_t LatencyHistogram::Count() const noexcept {
    return total_count_;
}

uint32_t LatencyHistogram::BucketIndex(uint64_t latency_ns) const noexcept {
    if (latency_ns < 100)        return 0;
    if (latency_ns < 200)        return 1;
    if (latency_ns < 500)        return 2;
    if (latency_ns < 1'000)      return 3;
    if (latency_ns < 2'000)      return 4;
    if (latency_ns < 5'000)      return 5;
    if (latency_ns < 10'000)     return 6;
    return 7;
}

uint64_t LatencyHistogram::Percentile(double percentile) const noexcept {
    if (total_count_ == 0) {
        return 0;
    }

    const uint64_t threshold =
        static_cast<uint64_t>(
            (percentile / 100.0) * static_cast<double>(total_count_)
        );

    uint64_t cumulative = 0;
    for (uint32_t i = 0; i < HISTOGRAM_BUCKET_COUNT; ++i) {
        cumulative += buckets_[i];
        if (cumulative >= threshold) {
            // Return upper bound of bucket as conservative estimate
            switch (i) {
                case 0: return 100;
                case 1: return 200;
                case 2: return 500;
                case 3: return 1'000;
                case 4: return 2'000;
                case 5: return 5'000;
                case 6: return 10'000;
                default: return 10'000;
            }
        }
    }

    return 10'000;
}

} // namespace Profiler
