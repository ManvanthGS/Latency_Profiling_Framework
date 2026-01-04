#include "reporter.hpp"

namespace Profiler {

void Reporter::WriteHumanReadable(
    const std::string& metric_name,
    const MetricSnapshot& s,
    std::ostream& os) {

    os << "[Profiler] " << metric_name << "\n";
    os << "  Count   : " << s.count << "\n";
    os << "  Mean(ns): " << s.mean_ns << "\n";
    os << "  Min(ns) : " << s.min_ns << "\n";
    os << "  Max(ns) : " << s.max_ns << "\n";
    os << "  P50(ns) : " << s.p50_ns << "\n";
    os << "  P95(ns) : " << s.p95_ns << "\n";
    os << "  P99(ns) : " << s.p99_ns << "\n";
    os << "\n";
}

void Reporter::WriteCsvHeader(std::ostream& os) {
    os << "metric,count,mean_ns,variance_ns,min_ns,max_ns,p50_ns,p95_ns,p99_ns\n";
}

void Reporter::WriteCsvRow(
    const std::string& metric_name,
    const MetricSnapshot& s,
    std::ostream& os) {

    os << metric_name << ","
       << s.count << ","
       << s.mean_ns << ","
       << s.variance_ns << ","
       << s.min_ns << ","
       << s.max_ns << ","
       << s.p50_ns << ","
       << s.p95_ns << ","
       << s.p99_ns << "\n";
}

} // namespace Profiler
