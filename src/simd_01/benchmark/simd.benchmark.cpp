#include "simd.h"

#include <random>

#include "benchmark/benchmark.h"

using namespace simd_01;

static order_book_t generate_order_book(const std::uint32_t depth) {
    std::random_device random_device;
    std::default_random_engine random_engine(random_device());
    std::uniform_real_distribution<std::float64_t> price_modifier_distribution(0.1, 1.0);
    std::uniform_int_distribution<std::uint32_t> quantity_distribution(1, 100'000);

    order_book_t order_book{
        .m_prices = std::vector<std::float64_t>(depth),
        .m_quantities = std::vector<std::float64_t>(depth),
        .m_depth = depth
    };
    std::float64_t price = 10.0;
    for (std::uint32_t i = 0; i < depth; ++i) {
        price += price_modifier_distribution(random_engine);
        order_book.m_prices.at(i) = price;
        order_book.m_quantities.at(i) = quantity_distribution(random_engine);
    }

    return order_book;
}

static void BM_scalar(benchmark::State& state) {
    const auto depth = static_cast<std::uint32_t>(state.range(0));
    const auto order_book = generate_order_book(depth);
    for (auto _ : state) {
        auto result = get_vwap(order_book);
        ::benchmark::DoNotOptimize(result);
        ::benchmark::ClobberMemory();
    }
}

static void BM_scalar_optimized_1(benchmark::State& state) {
    const auto depth = static_cast<std::uint32_t>(state.range(0));
    const auto order_book = generate_order_book(depth);
    for (auto _ : state) {
        auto result = get_vwap_opt(order_book);
        ::benchmark::DoNotOptimize(result);
        ::benchmark::ClobberMemory();
    }
}

static void BM_scalar_unrolled(benchmark::State& state) {
    const auto depth = static_cast<std::uint32_t>(state.range(0));
    const auto order_book = generate_order_book(depth);
    for (auto _ : state) {
        auto result = get_vwap_unrolled(order_book);
        ::benchmark::DoNotOptimize(result);
        ::benchmark::ClobberMemory();
    }
}

static void BM_avx2(benchmark::State& state) {
    const auto depth = static_cast<std::uint32_t>(state.range(0));
    const auto order_book = generate_order_book(depth);
    for (auto _ : state) {
        auto result = get_vwap_avx2(order_book);
        benchmark::DoNotOptimize(result);
        benchmark::ClobberMemory();
    }
}

BENCHMARK(BM_scalar)->Range(4, 512)->MinWarmUpTime(1.0);
BENCHMARK(BM_scalar_optimized_1)->Range(4, 512)->MinWarmUpTime(1.0);
BENCHMARK(BM_scalar_unrolled)->Range(4, 512)->MinWarmUpTime(1.0);
BENCHMARK(BM_avx2)->Range(4, 512)->MinWarmUpTime(1.0);
