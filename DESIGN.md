# Design Document — Latency Profiling Framework (V1)

## 1. Objective

The goal of this framework is to provide **accurate, low-overhead latency
profiling** for performance-critical C++ systems, with a strong emphasis on
**tail latency** rather than averages.

It is intended for:
- Low-latency and real-time systems
- Quantitative trading infrastructure
- Performance-sensitive backend services

---

## 2. Core Design Principles

1. Correctness before optimization
2. Deterministic behavior
3. No hot-path I/O or allocation
4. Clear separation of responsibilities
5. Explicit ownership and lifetimes
6. Zero cost when disabled

---

## 3. High-Level Architecture

```

+------------------------------+
|          User Code           |
|  PROFILER_SCOPE("Component") |
+---------------+--------------+
                |
                v
+---------------+--------------+
|          ScopedTimer         |
|   (RAII timing boundary)     |
+---------------+--------------+
                |
                v
+---------------+--------------+
|          MetricSink          |
|   - OnlineStats              |
|   - LatencyHistogram         |
+---------------+--------------+
                |
                v
+---------------+--------------+
|        MetricRegistry        |
|   (ownership & lifecycle)    |
+---------------+--------------+
                |
                v
+---------------+--------------+
|            Reporter          |
|        (text / CSV)          |
+------------------------------+

```

---

## 4. Measurement Layer

### 4.1 Clock Abstraction

- Uses `std::chrono::steady_clock`
- Monotonic and immune to system time changes
- Nanosecond resolution
- Chosen for correctness and portability

Raw CPU cycle counters are intentionally deferred to later versions.

---

### 4.2 Scoped RAII Timer

Latency measurement is bound to lexical scope using RAII.

Properties:
- Timing starts in the constructor
- Timing ends in the destructor
- Destructor is `noexcept`
- Copy and move operations are disabled

This guarantees:
- Exactly-once measurement
- Safety with early returns
- Correct behavior during exception unwinding
- No misuse by callers

---

## 5. Aggregation Layer

### 5.1 MetricSink

`MetricSink` is the aggregation boundary for a single metric.

Responsibilities:
- Accept latency samples
- Maintain online statistics
- Maintain a latency histogram
- Produce immutable snapshots

Non-responsibilities:
- No timing
- No formatting
- No I/O

Each sink owns its own mutex to protect internal invariants.

---

### 5.2 Online Statistics

Mean and variance are computed using **Welford’s algorithm**.

Properties:
- Single-pass
- Numerically stable
- No raw sample storage

Tracked values:
- Count
- Mean
- Variance
- Min
- Max

---

### 5.3 Latency Histogram

Percentiles are computed using a **fixed-bucket histogram**.

Design choices:
- Fixed bucket ranges
- Deterministic memory usage
- O(1) updates
- Conservative percentile estimation

Percentiles return the **upper bound of the bucket** to avoid
underestimating tail latency.

---

## 6. Registry Layer

### 6.1 MetricRegistry

The registry:
- Owns all `MetricSink` instances
- Maps metric names to sinks
- Controls sink lifetime
- Provides bulk reporting

Internal storage:
```

unordered_map<string, unique_ptr<MetricSink>>

```

Rationale:
- `MetricSink` contains a mutex and is non-movable
- Stable sink addresses are required
- Explicit ownership is preserved

The registry mutex protects:
- Map structure
- Sink creation
- Iteration during reporting

---

## 7. Reporting Layer

Reporting operates exclusively on **snapshots**.

Flow:
```

MetricSink
-> Snapshot()
-> Reporter
-> Text / CSV

````

Properties:
- Locks are held only during snapshot creation
- Formatting and I/O are lock-free
- Reporting never touches hot paths

---

## 8. User-Facing API

A macro façade provides ergonomic instrumentation.

```cpp
PROFILER_SCOPE("Component::Operation");
````

Internally, this:

* Expands to a `ScopedTimer`
* Retrieves the sink from the registry
* Preserves RAII semantics

This makes instrumentation:

* One-line
* Impossible to misuse
* Zero-overhead when disabled

---

## 9. Compile-Time Control

Profiling is controlled via `PROFILER_ENABLE`.

When disabled:

* Macros expand to no-ops
* No objects are instantiated
* No runtime branches exist

This guarantees zero runtime cost in production builds.

---

## 10. Threading Model (V1)

* Registry mutex protects global structure
* Sink mutex protects per-metric aggregation
* No global serialization of metrics

This design prioritizes correctness and clarity. Contention elimination
is deferred to V2.

---

## 11. Explicit Non-Goals (V1)

* Live tracing
* Event timelines
* Distributed tracing
* Background worker threads
* Dynamic histogram resizing

These are intentionally excluded to preserve determinism.

---

## 12. Version Evolution Strategy

### V2 — Scalability

* Thread-local sinks
* Lock-free hot paths
* Snapshot-time merging

### V3 — Precision

* CPU cycle counters (`rdtsc`)
* Calibration
* Pluggable clock strategies

### V4 — Distribution Accuracy

* HDR or logarithmic histograms
* Higher-order percentiles

### V5 — Tooling

* Regression comparison
* CI integration
* Performance baselines

---

## 13. Design Philosophy Summary

This framework is designed to:

* Make performance measurable
* Make tail latency visible
* Make misuse impossible
* Enable data-driven optimization

V1 establishes a clean, correct foundation on which higher-performance
features can be safely built.
