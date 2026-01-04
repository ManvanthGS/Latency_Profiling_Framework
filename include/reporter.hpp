#pragma once

#include <string>
#include <ostream>

#include "metric_sink.hpp"

namespace Profiler {

class Reporter {
public:
    static void WriteHumanReadable(
        const std::string& metric_name,
        const MetricSnapshot& snapshot,
        std::ostream& os);

    static void WriteCsvHeader(std::ostream& os);
    static void WriteCsvRow(
        const std::string& metric_name,
        const MetricSnapshot& snapshot,
        std::ostream& os);
};

} // namespace Profiler
