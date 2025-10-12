#include "fibonacci.h"
#include <benchmark/benchmark.h>

static void BM_fibonacci(benchmark::State& state) {
  for (auto _ : state) {
    benchmark::DoNotOptimize(fibonacci(100'000));
    benchmark::ClobberMemory();
  }
}

BENCHMARK(BM_fibonacci);

BENCHMARK_MAIN();
