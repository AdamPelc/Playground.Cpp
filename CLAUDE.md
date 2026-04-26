# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Build Commands

This project uses CMake presets with Ninja and vcpkg for dependency management. `$VCPKG_ROOT` must be set.

```bash
# Configure (choose a preset: release, debug, rel_with_deb_info, asan_ubsan, tsan)
cmake --preset <preset>

# Build
cmake --build out/build/<preset> --parallel

# Run all tests
ctest --test-dir out/build/<preset> --output-on-failure --parallel

# Run a single test executable directly
./out/build/<preset>/src/queue/test/queue.test

# Run a single test case (GTest filter)
./out/build/<preset>/src/queue/test/queue.test --gtest_filter="TestSuite.TestName"

# Run benchmarks
./out/build/<preset>/src/queue/benchmark/queue.benchmark
```

## Code Style

- **C++23** standard, enforced via `cpp_ver_23` interface library
- **clang-format**: Google-based style, 100 column limit, 4-space indent, `int* ptr` pointer style
- **clang-tidy**: extensive check list (bugprone, cert, cppcoreguidelines, modernize, performance, readability)
- **Compiler warnings**: `-Werror -Wall -Wextra -Wpedantic -Wconversion -Wshadow` and more, applied via `compiler_warnings` interface library — all warnings are errors

## Architecture

Each subproject under `src/` follows a consistent layout: `lib/` for the library, `test/` for GTest tests, `benchmark/` for Google Benchmark executables. CMake targets link against shared interface libraries `compiler_warnings` and `cpp_ver_23`.

Test targets are named `<project>.test`, benchmark targets `<project>.benchmark`. Libraries are added as CMake static/interface libraries and linked by their target name.

Dependencies (fmt, GTest, Google Benchmark) are managed via vcpkg (`vcpkg.json` manifest mode) and found with `find_package`.

## Sanitizer Presets

- `asan_ubsan` — AddressSanitizer + UndefinedBehaviorSanitizer
- `tsan` — ThreadSanitizer (Linux only, mutually exclusive with ASAN)