#include "metric_registry.hpp"

namespace Profiler {

MetricRegistry& MetricRegistry::Instance() noexcept {
    static MetricRegistry instance;
    return instance;
}

MetricSink& MetricRegistry::GetSink(const char* metric_name) noexcept {
    auto& instance = Instance();
    std::lock_guard<std::mutex> lock(instance.mutex_);

    auto it = instance.sinks_.find(metric_name);
    if (it == instance.sinks_.end()) {
        auto sink = std::make_unique<MetricSink>();
        auto [new_it, _] =
            instance.sinks_.emplace(metric_name, std::move(sink));
        return *new_it->second;
    }
    return *it->second;
}

void MetricRegistry::DumpAll(std::ostream& os) noexcept {
    auto& instance = Instance();
    std::lock_guard<std::mutex> lock(instance.mutex_);

    for (const auto& [name, sink] : instance.sinks_) {
        auto snapshot = sink->Snapshot();
        Reporter::WriteHumanReadable(name, snapshot, os);
    }
}

void MetricRegistry::DumpAllCsv(std::ostream& os) noexcept {
    auto& instance = Instance();
    std::lock_guard<std::mutex> lock(instance.mutex_);

    Reporter::WriteCsvHeader(os);
    for (const auto& [name, sink] : instance.sinks_) {
        auto snapshot = sink->Snapshot();
        Reporter::WriteCsvRow(name, snapshot, os);
    }
}

} // namespace Profiler
