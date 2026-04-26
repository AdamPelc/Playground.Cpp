# Playground.Cpp

A C++ playground repository containing various experiments, algorithms, design patterns, and performance benchmarks.

## Requirements

- CMake 3.31 or higher
- Ninja
- C++23 compatible compiler (GCC 11+, Clang 14+)
- [vcpkg](https://github.com/microsoft/vcpkg) with `$VCPKG_ROOT` set

## Building

Dependencies (`fmt`, `gtest`, `benchmark`) are managed via vcpkg manifest mode and installed automatically during configure.

```bash
# Configure (presets: release, debug, rel_with_deb_info, asan_ubsan, tsan)
cmake --preset <preset>

# Build
cmake --build out/build/<preset> --parallel
```

### Running Tests

```bash
ctest --test-dir out/build/<preset> --output-on-failure --parallel
```

Or run a single test executable directly:

```bash
./out/build/<preset>/src/queue/test/queue.test

# With GTest filter
./out/build/<preset>/src/queue/test/queue.test --gtest_filter="TestSuite.TestName"
```

### Running Benchmarks

```bash
./out/build/<preset>/src/queue/benchmark/queue.benchmark
```

### Sanitizer Presets

- `asan_ubsan` — AddressSanitizer + UndefinedBehaviorSanitizer
- `tsan` — ThreadSanitizer (Linux only, mutually exclusive with ASAN)

## Contents

### Algorithms & Data Structures
- **algorithms/** - Data structures and graph algorithms
- **LeetCode/** - LeetCode problem solutions

### Design Patterns
- **P001.VisitorDesignPattern/** - Classic visitor pattern
- **P002.VisitorDesignPatternGeneric/** - Generic visitor pattern using modern C++ templates
- **CustomIterator/** - Custom iterator implementations

### Performance & Optimization
- **performance/** - CPU frequency scaling and Fibonacci benchmarks
- **queue/** - Lock-free queue implementations with benchmarks and tests
- **simd_01/** - SIMD (AVX2) experiments: scalar, unrolled, and vectorized implementations

### Other
- **P003.Spectre/** - Spectre vulnerability exploration
- **Book/** - Code examples from "The Art of Writing Efficient Programs"

## Code Style

- C++23 standard
- clang-format (Google-based, 100 column limit, 4-space indent)
- clang-tidy with extensive checks
- All warnings treated as errors (`-Werror -Wall -Wextra -Wpedantic`)