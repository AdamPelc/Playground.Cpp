#include "spsc_queue.h"

#include <benchmark/benchmark.h>
#include <fmt/base.h>

#define REPEAT2(x)  x; x;
#define REPEAT4(x)  REPEAT2(x) REPEAT2(x)
#define REPEAT8(x)  REPEAT4(x) REPEAT4(x)
#define REPEAT16(x) REPEAT8(x) REPEAT8(x)
#define REPEAT32(x) REPEAT16(x) REPEAT16(x)
#define REPEAT64(x) REPEAT32(x) REPEAT32(x)

static spsc_queue_t<int, impl::queue_mutex_t> queue;

void BM_spsc_queue_enqueue_dequeue_small_elements(benchmark::State& state) {
    const auto is_producer = state.thread_index() & 1;
    for (auto _ : state) {
        if (is_producer) {
            for (int i = 0; i < 100; ++i) {
                REPEAT64(queue.enqueue(i))
            }
        } else {
            for (int i = 0; i < 100; ++i) {
                REPEAT64(benchmark::DoNotOptimize(                       queue.dequeue()))
            }
        }
    }

    state.SetItemsProcessed(state.iterations() * 64 * 100);
}

BENCHMARK(BM_spsc_queue_enqueue_dequeue_small_elements)->Threads(2);
BENCHMARK_MAIN();
