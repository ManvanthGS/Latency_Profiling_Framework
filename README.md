# Latency Profiling Framework (V1)

A low-overhead C++ latency profiling framework for performance-critical and
low-latency systems.

This framework measures what actually matters in real systems: **tail
latency**. It uses RAII-based scoped timing, online aggregation, and percentile
analysis (p50 / p95 / p99), while compiling to **zero cost when disabled**.

V1 focuses on correctness, determinism, and clean architecture. It is meant to
be a solid foundation for future high-performance extensions.

---

## Key Features (V1)

- RAII-based scoped latency measurement
- Monotonic, stable clock source
- Online statistics (no raw sample storage)
- Tail latency percentiles (p50 / p95 / p99)
- Thread-safe aggregation
- Central metric registry
- One-line instrumentation via macros
- Human-readable and CSV reporting
- Compile-time enable / disable (zero runtime overhead when off)

---

## Example Usage

### Instrumentation

```cpp
#include "macros.hpp"

void TestFunction() {
    PROFILER_SCOPE("Profile::TestFunction");
    // hot path logic
}
````

### Reporting at Shutdown

```cpp
#include "metric_registry.hpp"

Profiler::MetricRegistry::DumpAll(std::cout);

std::ofstream csv("latency.csv");
Profiler::MetricRegistry::DumpAllCsv(csv);
```

---

## Example Output

### Human-Readable

```text
[Profiler] Profile::TestFunction
  Count   : 4,812,903
  Mean(ns): 410
  Min(ns) : 120
  Max(ns) : 8400
  P50(ns) : 500
  P95(ns) : 720
  P99(ns) : 1900
```

### CSV

```csv
metric,count,mean_ns,variance_ns,min_ns,max_ns,p50_ns,p95_ns,p99_ns
OrderBook::AddOrder,4812903,410,1.2e5,120,8400,500,720,1900
```

---

## Compile-Time Control

Profiling can be fully compiled out.

```cmake
target_compile_definitions(${TARGET_NAME} PRIVATE include)
```

If `PROFILER_ENABLE` is not defined, all profiling code is removed at compile
time with zero runtime overhead.

---

## Design Principles

* Measurement, aggregation, and reporting are strictly separated
* No I/O or formatting on hot paths
* Deterministic memory usage
* Conservative tail-latency reporting
* Explicit ownership and lifetimes
* Correctness before optimization

---

## Version Roadmap

### V2 — Scalability & Contention Elimination

* Thread-local metric sinks
* Lock-free or low-contention aggregation
* Stable p99 under high concurrency

### V3 — High-Precision Timing

* Optional `rdtsc` / `rdtscp` backend
* Calibration to nanoseconds
* Pluggable clock strategies

### V4 — Advanced Percentiles

* HDR or logarithmic histograms
* p99.9 / p99.99
* Distribution-level analysis

### V5 — Tooling & Regression Detection

* Baseline comparison
* Performance regression detection
* CI integration
* Optional JSON export

---

## Non-Goals

* Live tracing or per-event logging
* Distributed tracing
* Background threads
* Heavy runtime configuration
* Observability dashboards

This framework is intentionally focused on profiling, not tracing or
observability.

---
