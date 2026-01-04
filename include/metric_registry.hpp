#pragma once

#include <unordered_map>
#include <string>
#include <mutex>
#include <ostream>
#include <memory>

#include "metric_sink.hpp"
#include "reporter.hpp"

namespace Profiler {

class MetricRegistry {
public:
    static MetricSink& GetSink(const char* metric_name) noexcept;

    static void DumpAll(std::ostream& os) noexcept;
    static void DumpAllCsv(std::ostream& os) noexcept;

private:
    static MetricRegistry& Instance() noexcept;

private:
    MetricRegistry() = default;

    mutable std::mutex mutex_;
    std::unordered_map<std::string, std::unique_ptr<MetricSink>> sinks_;
};

} // namespace Profiler
