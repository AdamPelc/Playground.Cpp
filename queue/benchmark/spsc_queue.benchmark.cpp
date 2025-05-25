#include "spsc_queue.h"

#include <benchmark/benchmark.h>
#include <fmt/base.h>
#include <random>

#include "impl/queue_wip.hpp"

#define REPEAT2(x)  x; x;
#define REPEAT4(x)  REPEAT2(x) REPEAT2(x)
#define REPEAT8(x)  REPEAT4(x) REPEAT4(x)
#define REPEAT16(x) REPEAT8(x) REPEAT8(x)
#define REPEAT32(x) REPEAT16(x) REPEAT16(x)
#define REPEAT64(x) REPEAT32(x) REPEAT32(x)

static spsc_queue_t<int, impl::queue_mutex_t> queue(10'000);

void BM_spsc_queue_enqueue_dequeue_small_elements(benchmark::State& state) {
    const auto is_producer = state.thread_index() & 1;
    for (auto _ : state) {
        if (is_producer) {
            for (int i = 0; i < 100; ++i) {
                REPEAT64(queue.enqueue(i))
            }
        } else {
            for (int i = 0; i < 100; ++i) {
                REPEAT64(benchmark::DoNotOptimize(                       queue.try_dequeue()))
            }
        }
    }

    state.SetItemsProcessed(state.iterations() * 64 * 100);
}

static spsc_queue_t<int, impl::queue_wip_t> queue2(10'000);
void BM_spsc_queue2_enqueue_dequeue_small_elements(benchmark::State& state) {
    const auto is_producer = state.thread_index() & 1;
    for (auto _ : state) {
        if (is_producer) {
            for (int i = 0; i < 100; ++i) {
                REPEAT64(queue2.enqueue(i))
            }
        } else {
            for (int i = 0; i < 100; ++i) {
                REPEAT64(benchmark::DoNotOptimize(                       queue2.try_dequeue()))
            }
        }
    }

    state.SetItemsProcessed(state.iterations() * 64 * 100);
}

static std::vector<std::uint8_t> buffer(65536);
static spsc_queue_t<std::vector<std::uint8_t>> big_queue(10'000);
void BM_spsc_queue_enqueue_dequeue_64kB_elements(benchmark::State& state) {
    const auto is_producer = state.thread_index() & 1;
    constexpr auto loop_iterations = 10;

    for (auto _ : state) {
        if (is_producer) {
            for (int i = 0; i < loop_iterations; ++i) {
                REPEAT64(big_queue.enqueue(buffer))
            }
        } else {
            for (int i = 0; i < loop_iterations; ++i) {
                REPEAT64(benchmark::DoNotOptimize(big_queue.try_dequeue()))
            }
        }
    }

    state.SetItemsProcessed(state.iterations() * 64 * loop_iterations);
}

static spsc_queue_t<std::vector<std::uint8_t>, impl::queue_wip_t> big_queue2(10'000);
void BM_spsc_queue2_enqueue_dequeue_64kB_elements(benchmark::State& state) {
    const auto is_producer = state.thread_index() & 1;
    constexpr auto loop_iterations = 10;

    for (auto _ : state) {
        if (is_producer) {
            for (int i = 0; i < loop_iterations; ++i) {
                REPEAT64(big_queue2.enqueue(buffer))
            }
        } else {
            for (int i = 0; i < loop_iterations; ++i) {
                REPEAT64(benchmark::DoNotOptimize(big_queue2.try_dequeue()))
            }
        }
    }

    state.SetItemsProcessed(state.iterations() * 64 * loop_iterations);
}

BENCHMARK(BM_spsc_queue_enqueue_dequeue_small_elements)->Threads(2);
BENCHMARK(BM_spsc_queue2_enqueue_dequeue_small_elements)->Threads(2);
BENCHMARK(BM_spsc_queue_enqueue_dequeue_64kB_elements)->Threads(2);
BENCHMARK(BM_spsc_queue2_enqueue_dequeue_64kB_elements)->Threads(2);
BENCHMARK_MAIN();
