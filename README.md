# Playground.Cpp

A C++ playground repository containing various experiments, algorithms, design patterns, and performance benchmarks.

## Contents

This repository includes the following components:

### Algorithms & Data Structures
- **algorithms/** - Implementation of various algorithms including:
  - Data structures
  - Graph algorithms
- **LeetCode/** - Solutions to LeetCode problems

### Design Patterns
- **P001.VisitorDesignPattern/** - Classic visitor pattern implementation
- **P002.VisitorDesignPatternGeneric/** - Generic visitor pattern using modern C++ templates
- **CustomIterator/** - Custom iterator implementations

### Performance & Optimization
- **performance/** - Performance experiments including:
  - CPU frequency scaling tests
  - Fibonacci implementation benchmarks
- **InstructionLevelParallelism/** - Instruction-level parallelism (ILP) demonstrations
- **P003.Spectre/** - Spectre vulnerability exploration
- **queue/** - Lock-free queue implementations with benchmarks and tests

### Book Examples
- **Book/** - Code examples from "The Art of Writing Efficient Programs"

## Requirements

- CMake 3.22 or higher
- C++23 compatible compiler (GCC 11+, Clang 14+, or MSVC 2022+)
- vcpkg or system package manager for dependencies

### Dependencies

The following libraries are required:
- **fmt** - Modern formatting library
- **GTest** - Google Test framework for unit tests
- **benchmark** - Google Benchmark for performance testing

## Building

### Using vcpkg (Recommended)

1. Install dependencies via vcpkg:
```bash
vcpkg install fmt gtest benchmark
```

2. Configure the project:
```bash
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=[path-to-vcpkg]/scripts/buildsystems/vcpkg.cmake
```

3. Build:
```bash
cmake --build build
```

### Alternative Build Methods

If dependencies are installed system-wide:

```bash
cmake -B build -S .
cmake --build build
```

### Running Tests

Tests are built automatically and can be run with:

```bash
cd build
ctest
```

Or run test executables directly from the build directory.

### Running Benchmarks

Benchmark executables are located in the build directory structure matching the source layout:

```bash
# Example: Run queue benchmarks
./build/queue/benchmark/queue_benchmark
```

## Development

The project uses:
- C++23 standard
- Strict compiler warnings (-Wall -Werror -Wextra -pedantic)
- `.clang-format` for code formatting
- `.clang-tidy` for static analysis
