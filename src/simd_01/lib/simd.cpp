#include "simd.h"

#include <cstddef>
#include <immintrin.h>

namespace simd_01 {

[[nodiscard]] std::float64_t get_vwap(const order_book_t& order_book) noexcept {
    const auto depth = order_book.m_depth;
    if (depth == 0) {
        return 0.0;
    }

    const auto* prices = order_book.m_prices.data();
    const auto* quantities = order_book.m_quantities.data();

    std::float64_t sum_weighted = 0.0;
    std::float64_t sum_qty = 0.0;

    for (std::size_t i = 0; i < depth; ++i) {
        const auto qty = quantities[i];
        const auto price = prices[i];
        sum_weighted += price * qty;
        sum_qty += qty;
    }

    if (sum_qty == 0.0) {
        return 0.0;
    }
    return sum_weighted / sum_qty;
}

std::float64_t get_vwap_opt(const order_book_t& order_book) noexcept {
    const auto depth = order_book.m_depth;
    if (depth == 0) {
        return 0.0;
    }

    const auto* __restrict prices = order_book.m_prices.data();
    const auto* __restrict quantities = order_book.m_quantities.data();

    std::float64_t sum_weighted = 0.0;
    std::float64_t sum_qty = 0.0;

#pragma GCC ivdep
    for (std::size_t i = 0; i < depth; ++i) {
        const auto qty = quantities[i];
        const auto price = prices[i];
        sum_weighted += price * qty;
        sum_qty += qty;
    }

    if (sum_qty == 0.0) {
        return 0.0;
    }
    return sum_weighted / sum_qty;
}

std::float64_t get_vwap_unrolled(const order_book_t& order_book) noexcept {
    const auto depth = order_book.m_depth;
    if (depth == 0) {
        return 0.0;
    }

    const auto* prices = order_book.m_prices.data();
    const auto* quantities = order_book.m_quantities.data();

    std::float64_t weighted0 = 0.0;
    std::float64_t weighted1 = 0.0;
    std::float64_t weighted2 = 0.0;
    std::float64_t weighted3 = 0.0;
    std::float64_t qty0 = 0.0;
    std::float64_t qty1 = 0.0;
    std::float64_t qty2 = 0.0;
    std::float64_t qty3 = 0.0;

    std::size_t i = 0;
    for (; i + 4 <= depth; i += 4) {
        weighted0 += prices[i] * quantities[i];
        weighted1 += prices[i + 1] * quantities[i + 1];
        weighted2 += prices[i + 2] * quantities[i + 2];
        weighted3 += prices[i + 3] * quantities[i + 3];
        qty0 += quantities[i];
        qty1 += quantities[i + 1];
        qty2 += quantities[i + 2];
        qty3 += quantities[i + 3];
    }
    for (; i < depth; ++i) {
        weighted0 += prices[i] * quantities[i];
        qty0 += quantities[i];
    }

    auto sum_weighted = weighted0 + weighted1 + weighted2 + weighted3;
    auto sum_qty = qty0 + qty1 + qty2 + qty3;

    if (sum_qty == 0.0) {
        return 0.0;
    }
    return sum_weighted / sum_qty;
}

std::float64_t get_vwap_avx2(const order_book_t& order_book) noexcept {
    if (order_book.m_depth == 0) {
        return 0.0;
    }

    alignas(32) const double zeros[4] = {0.0, 0.0, 0.0, 0.0};
    __m256d total_sum_weighted_simd = _mm256_load_pd(zeros);
    __m256d sum_qty_simd = _mm256_load_pd(zeros);
    for (std::size_t i = 0; i < order_book.m_depth; i += 4) {
        const auto* qty = &order_book.m_quantities[i];
        const auto* price = &order_book.m_prices[i];
        __m256d qty_simd = _mm256_loadu_pd(reinterpret_cast<const double*>(qty));
        sum_qty_simd = _mm256_add_pd(sum_qty_simd, qty_simd);
        __m256d price_simd = _mm256_loadu_pd(reinterpret_cast<const double*>(price));
        __m256d sum_weighted_simd = _mm256_mul_pd(qty_simd, price_simd);
        total_sum_weighted_simd = _mm256_add_pd(total_sum_weighted_simd, sum_weighted_simd);
    }

    alignas(32) double weighted_lanes[4];
    alignas(32) double qty_lanes[4];
    _mm256_store_pd(weighted_lanes, total_sum_weighted_simd);
    _mm256_store_pd(qty_lanes, sum_qty_simd);

    std::float64_t sum_weighted = 0.0;
    std::float64_t sum_qty = 0.0;
    for (std::size_t i = 0; i < 4; ++i) {
        sum_weighted += weighted_lanes[i];
        sum_qty += qty_lanes[i];
    }

    return sum_weighted / sum_qty;
}

}  // namespace simd_01
