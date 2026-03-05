# Benchmarking – Performance Measurement in C

This project focuses on measuring and comparing the performance of C programs using CPU time instrumentation. It explores the relationship between algorithm complexity, runtime, and energy efficiency.

## Files

| File | Description |
|------|-------------|
| `baseline_loop.c` | A simple loop running 100,000,000 iterations to establish a baseline execution time |
| `baseline_loop-metrics.md` | Recorded execution times for the baseline loop across three test runs |
| `instrumentation_lab.c` | Multi-phase program that measures dataset building, processing, and checksum reduction times independently |
| `comparison_algorithms-metrics.md` | Comparative execution times for a naive O(n²) algorithm vs. a single-pass O(n) algorithm |
| `green_efficiency_analysis.md` | Analysis of runtime differences, energy implications, and engineering takeaways |

## Concepts Covered

- CPU time measurement using `clock()` from `<time.h>`
- Per-phase instrumentation with separate `clock_t` variables
- Comparing algorithmic complexity (O(n²) vs O(n)) through empirical measurement
- Relationship between runtime and energy consumption
- Controlled experiment methodology (multiple runs, average calculation)

## Key Results

- The naive algorithm (~1.345 s) is approximately **24 743×** slower than the single-pass algorithm (~0.000054 s)
- Per-phase profiling reveals that dataset building is the most expensive phase in `instrumentation_lab.c`
- Algorithmic efficiency directly reduces both runtime and implied energy usage

## Requirements

- All C files are compiled with `gcc -Wall -Werror -Wextra -pedantic -std=gnu89`
- Programs are compiled and measured on Ubuntu 20.04 LTS
- Timing uses `clock()` (CPU time)

## Author

Holberton School – Low Level Programming
