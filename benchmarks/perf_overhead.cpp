#include <iostream>
#include <chrono>
#include "profiler/macros.hpp"

int main() {
    constexpr int iterations = 1'000'000;

    auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < iterations; ++i) {
        PROFILER_SCOPE("OverheadTest");
    }
    auto end = std::chrono::steady_clock::now();

    auto total_ns =
        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    std::cout << "Total ns: " << total_ns << "\n";
    std::cout << "Avg per scope (ns): "
              << total_ns / iterations << "\n";
}
