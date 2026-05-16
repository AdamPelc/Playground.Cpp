#include "01_no_vector.h"
#include "02_vector_no_fast_math.h"
#include "03_vector_fast_math.h"
#include "04_manual_simd.h"

#include <random>
#include <benchmark/benchmark.h>

static order_book_t generate_order_book(const std::uint32_t depth) {
    std::random_device random_device;
    std::default_random_engine random_engine(random_device());
    std::uniform_real_distribution price_modifier_distribution(0.1f, 1.f);
    std::uniform_real_distribution quantity_distribution(1.f, 100'000.f);

    order_book_t order_book{
        .m_prices = std::vector<float>(depth),
        .m_quantities = std::vector<float>(depth),
    };
    auto price = 10.0f;
    for (std::uint32_t i = 0; i < depth; ++i) {
        price += price_modifier_distribution(random_engine);
        order_book.m_prices.at(i) = price;
        order_book.m_quantities.at(i) = quantity_distribution(random_engine);
    }

    return order_book;
}

static void BM_01_no_vector(benchmark::State& state) {
    const auto depth = static_cast<std::uint32_t>(state.range(0));
    const auto order_book = generate_order_book(depth);
    for (auto _ : state) {
        auto result = calculate_vwap_no_vector(order_book);
        ::benchmark::DoNotOptimize(result);
        ::benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_01_no_vector)->Arg(262144)->MinWarmUpTime(1.0);

static void BM_02_vector_no_fast_math(benchmark::State& state) {
    const auto depth = static_cast<std::uint32_t>(state.range(0));
    const auto order_book = generate_order_book(depth);
    for (auto _ : state) {
        auto result = calculate_vwap_vector_no_fast_math(order_book);
        ::benchmark::DoNotOptimize(result);
        ::benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_02_vector_no_fast_math)->Arg(262144)->MinWarmUpTime(1.0);

static void BM_03_vector_fast_math(benchmark::State& state) {
    const auto depth = static_cast<std::uint32_t>(state.range(0));
    const auto order_book = generate_order_book(depth);
    for (auto _ : state) {
        auto result = calculate_vwap_vector_fast_math(order_book);
        ::benchmark::DoNotOptimize(result);
        ::benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_03_vector_fast_math)->Arg(262144)->MinWarmUpTime(1.0);

static void BM_04_manual_simd(benchmark::State& state) {
    const auto depth = static_cast<std::uint32_t>(state.range(0));
    const auto order_book = generate_order_book(depth);
    for (auto _ : state) {
        auto result = calculate_vwap_manual_simd(order_book);
        ::benchmark::DoNotOptimize(result);
        ::benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_04_manual_simd)->Arg(262144)->MinWarmUpTime(1.0);
