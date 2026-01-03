# latency_metrics — Latency Profiling Framework

A small, header-first C++ framework for low-overhead, in-process latency measurement aimed at performance-critical code paths (order book, event dispatch, matching logic). It provides RAII scoped timers, fixed-bucket histograms with nanosecond resolution, and end-of-run reporting (human-readable text and CSV). The V1 design prioritizes deterministic performance: no dynamic allocation in hot paths, O(1) recording, and predictable memory use.

## Goals
- Record scope/function latency with nanosecond precision.
- Produce accurate tail statistics: p50, p95, p99.
- Keep hot-path overhead < 100 ns and zero allocations.
- Simple multi-threaded aggregation with a path to TLS-based sinks in later versions.

## Timing Source

V1 uses `std::chrono::steady_clock` to guarantee monotonic,
OS-stable timestamps suitable for tail-latency analysis.

Raw CPU counters (rdtsc) are intentionally deferred to later
versions to avoid calibration and cross-core issues.

## Scoped Timing

Latency is measured using an RAII-based `ScopedTimer`.
Timing starts on construction and is recorded on destruction,
ensuring correctness even with early returns or exceptions.


```cpp
// pseudo: include the public header (implementation pending)
#include "latency_metrics.h"

void processOrder() {
    // start timing automatically at construction, stop at scope exit
    latency_metrics::ScopedTimer timer("OrderBook::AddOrder");
    // ... hot-path work ...
}

// At end-of-run, dump aggregated reports:
latency_metrics::Registry::Instance().DumpText(std::cout);
latency_metrics::Registry::Instance().WriteCsv("latency_report.csv");
```

Note: APIs above are illustrative and follow the V1 DESIGN.md intent (see DESIGN.md for exact API decisions).

## Example output
```
[Latency] OrderBook::AddOrder
Count: 4,812,903
Mean: 410 ns
StdDev: 120 ns
p50: 390 ns
p95: 720 ns
p99: 1.9 µs
Max: 8.4 µs
```

CSV output should contain one row per measured scope with columns such as: name, count, min_ns, max_ns, mean_ns, stddev_ns, p50_ns, p95_ns, p99_ns.

## Build & integration
- Header-first design for easy inclusion in existing projects.
- Provide an optional small .cpp for heavier aggregation/reporting code.
- Intended to work with CMake; no third-party dependencies (minimal STL only).

## Where to look next
- See DESIGN.md for the full V1 scope, non-scope items, and the versioned roadmap (V2..V4).
- Next implementation steps:
  - Implement a header-only ScopedTimer and fixed-bucket histogram with nanosecond storage.
  - Provide a simple Registry for aggregation and text/CSV exporters.
  - Add unit tests and a small CMake example project.
