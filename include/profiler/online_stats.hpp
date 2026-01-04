#pragma once

#include <cstdint>
#include <limits>

namespace Profiler {

class OnlineStats {
public:
    OnlineStats() noexcept;

    void Add(uint64_t value) noexcept;

    uint64_t Count() const noexcept;
    double Mean() const noexcept;
    double Variance() const noexcept;

    uint64_t Min() const noexcept;
    uint64_t Max() const noexcept;

private:
    uint64_t count_;
    double mean_;
    double m2_;
    uint64_t min_;
    uint64_t max_;
};

} // namespace Profiler
