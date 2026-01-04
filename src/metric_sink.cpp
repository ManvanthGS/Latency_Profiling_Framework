#include "metric_sink.hpp"

namespace Profiler {

MetricSink::MetricSink() noexcept = default;

void MetricSink::Record(uint64_t latency_ns) noexcept {
    std::lock_guard<std::mutex> lock(mutex_);
    stats_.Add(latency_ns);
}

MetricSnapshot MetricSink::Snapshot() const noexcept {
    std::lock_guard<std::mutex> lock(mutex_);

    MetricSnapshot snapshot{};
    snapshot.count = stats_.Count();
    snapshot.mean_ns = stats_.Mean();
    snapshot.variance_ns = stats_.Variance();
    snapshot.min_ns = stats_.Min();
    snapshot.max_ns = stats_.Max();

    snapshot.p50_ns = histogram_.Percentile(50.0);
    snapshot.p95_ns = histogram_.Percentile(95.0);
    snapshot.p99_ns = histogram_.Percentile(99.0);

    return snapshot;
}

} // namespace Profiler
