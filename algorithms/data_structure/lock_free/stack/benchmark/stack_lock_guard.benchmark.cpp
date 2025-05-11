#include "stack_lock_guard.hpp"

#include "mutex/mutex_v1.hpp"
#include "stack_mutex.hpp"

#include <benchmark/benchmark.h>
#include <latch>

template<template<class, class> class TStack, class TMutex>
static void BM_ReadOnlyFromTheTop(benchmark::State& state)
{
    static TStack<int, TMutex> stack;
    stack.push(1);

    if (state.thread_index() == 0) {
        stack.reset();
    }

    std::latch latch(state.threads());

    for (auto _ : state) {
        benchmark::DoNotOptimize(stack.top());
    }

    state.SetItemsProcessed(state.iterations());
}

template<template<class, class> class TStack, class TMutex>
static void BM_PushAndPop(benchmark::State& state)
{
    static TStack<int, TMutex> stack;

    if (state.threads() & 1)
    {
        state.SkipWithError("Odd number of threads");
        return;
    }

    if (state.thread_index() == 0) {
        stack.reset();
    }

    const bool is_producer = state.thread_index() & 1;
    std::latch latch(state.threads());

    for (auto _ : state)
    {
        if (is_producer)
            stack.push(0xBEEF);
        else
            stack.pop();
    }
    state.SetItemsProcessed(state.iterations());
}


/*
 * 2.  Register one instantiation per implementation.  Adding yet another
 *     stack only requires another BENCHMARK_TEMPLATE line.
 */
BENCHMARK_TEMPLATE(BM_ReadOnlyFromTheTop, stack_mutex_t, std::shared_mutex)->ThreadRange(1, 64);
BENCHMARK_TEMPLATE(BM_ReadOnlyFromTheTop, stack_mutex_t, mutex_v1_t)->ThreadRange(1, 64);

BENCHMARK_TEMPLATE(BM_PushAndPop,      stack_mutex_t, std::shared_mutex)  ->ThreadRange(1, 64);
BENCHMARK_TEMPLATE(BM_PushAndPop,      stack_mutex_t, mutex_v1_t)  ->ThreadRange(1, 64);

BENCHMARK_MAIN();
