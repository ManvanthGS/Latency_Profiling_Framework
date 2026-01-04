#include "online_stats.hpp"

namespace Profiler {

OnlineStats::OnlineStats() noexcept
    : count_(0),
      mean_(0.0),
      m2_(0.0),
      min_(std::numeric_limits<uint64_t>::max()),
      max_(0) {}

void OnlineStats::Add(uint64_t value) noexcept {
    ++count_;

    const double delta = static_cast<double>(value) - mean_;
    mean_ += delta / static_cast<double>(count_);
    const double delta2 = static_cast<double>(value) - mean_;
    m2_ += delta * delta2;

    if (value < min_) min_ = value;
    if (value > max_) max_ = value;
}

uint64_t OnlineStats::Count() const noexcept {
    return count_;
}

double OnlineStats::Mean() const noexcept {
    return mean_;
}

double OnlineStats::Variance() const noexcept {
    return (count_ > 1) ? (m2_ / static_cast<double>(count_ - 1)) : 0.0;
}

uint64_t OnlineStats::Min() const noexcept {
    return (count_ > 0) ? min_ : 0;
}

uint64_t OnlineStats::Max() const noexcept {
    return (count_ > 0) ? max_ : 0;
}

} // namespace Profiler
