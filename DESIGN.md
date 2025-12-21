# Latency Profiling Framework — DESIGN.md

## V1 — Core Scope (V1: Implement and ship)
### One-line goal
Provide low-overhead, in-process latency measurement with accurate tail statistics (p50/p95/p99) for performance-critical C++ code paths.

### What this framework IS (V1)
- Scoped, RAII-based timing for measuring execution latency of code scopes/functions.
- Focus on hot paths (order book, event dispatch, matching logic).
- Multi-threaded support with end-of-run reporting (text + CSV).
- Header-first design; optional .cpp for heavy logic. CMake-friendly.

### Measurement model (V1)
- RAII scope timers: start on construction, stop on destruction.
- No required stop calls (works with exceptions/early returns).
- Internal storage: nanoseconds. Percentiles computed in ns; reporting can format ns/µs/ms.

### Metrics collected (V1)
For each measured scope/component:
- Count, Min, Max, Mean, Std deviation, p50, p95, p99
Notes: p99.9 and external histograms are out of scope for V1.

### Percentile strategy (V1)
- Fixed bucket histogram with deterministic memory usage.
- Percentiles derived from cumulative bucket counts.
- No dynamic bucket resizing in V1.

### Threading model (V1)
- Thread-safe aggregation.
- V1 implementation: simple mutex-protected global registry OR thread-local sinks merged at report time.
- API designed so swapping mutex → TLS does not change user code.

### Performance constraints (hard, V1)
- No dynamic allocation in hot path.
- Scoped timing overhead < 100 ns target.
- Recording is O(1).

### Reporting (V1)
- End-of-run only.
- Output: human-readable text + CSV.
- Example snippet:
  [Latency] OrderBook::AddOrder
  Count: 4,812,903
  Mean: 410 ns
  p95: 720 ns
  p99: 1.9 µs
  Max: 8.4 µs

### Build & Integration (V1)
- Header-first; optional small .cpp.
- Works with CMake.
- No external dependencies beyond minimal STL.

## Explicit NON-SCOPE (Intentional for V1)
- No live/real-time visualization or dashboards.
- No distributed tracing or cross-process correlation.
- No per-event logs, flame graphs, or timeline reconstruction.
- No adaptive/dynamic histogram resizing.
- No third-party libs (no Boost, no external histogram libraries).

## V2 — Performance & Scalability Upgrade (post-V1)
**Additions**
- Thread-local metric sinks (TLS).
- Lock-free or wait-free aggregation.
- Better percentile accuracy (HDR-style buckets).
- Configurable bucket layouts.

**Why V2 exists**
- Reduce contention under high thread counts.
- Improve p99 stability.

## V3 — System-Level Profiling (optional, advanced)
**Additions**
- Per-core statistics
- CPU affinity awareness
- NUMA-aware aggregation
- Per-phase metrics (decode / match / publish)

Notes: This is HFT-grade territory and optional after V2 stabilization.

## V4 — Tooling & Integration (optional)
**Additions**
- JSON output
- Diff-based regression comparison
- CLI tool to compare two runs

## Naming guidance
Prefer boring, professional names:
- latency_metrics, perf_latency, rt_latency

## Quick implementation notes / constraints (reminder)
- Keep hot path zero/allocation-free.
- Design APIs to allow swapping underlying aggregation (mutex ↔ TLS) with minimal caller changes.
- Prefer deterministic memory usage for histograms in V1.
