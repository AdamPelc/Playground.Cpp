#include "04_manual_simd.h"

#include <cstddef>
#include <immintrin.h>
#include <array>

float calculate_vwap_manual_simd(const order_book_t& order_book) noexcept
{
    const auto depth = std::size(order_book.m_prices);
    if (depth == 0) {
        return {};
    }

    constexpr std::array<float, 8> zeros = {};
    __m256 total_sum_weighted_simd = _mm256_loadu_ps(zeros.data());
    __m256 sum_qty_simd = _mm256_loadu_ps(zeros.data());
    for (std::size_t i = 0; i < depth; i += 8) {
        const auto* qty = &order_book.m_quantities[i];
        const auto* price = &order_book.m_prices[i];
        const __m256 qty_simd = _mm256_loadu_ps(qty);
        sum_qty_simd = _mm256_add_ps(sum_qty_simd, qty_simd);
        const __m256 price_simd = _mm256_loadu_ps(price);
        const __m256 sum_weighted_simd = _mm256_mul_ps(qty_simd, price_simd);
        total_sum_weighted_simd = _mm256_add_ps(total_sum_weighted_simd, sum_weighted_simd);
    }

    std::array<float,8> weighted_lanes{};
    std::array<float,8> qty_lanes{};
    _mm256_storeu_ps(weighted_lanes.data(), total_sum_weighted_simd);
    _mm256_storeu_ps(qty_lanes.data(), sum_qty_simd);

    float sum_weighted = 0.0f;
    float sum_qty = 0.0f;
    for (std::size_t i = 0; i < 8; ++i) {
        sum_weighted += weighted_lanes[i];
        sum_qty += qty_lanes[i];
    }

    if (sum_qty == 0.0f) {
        return {};
    }

    return sum_weighted / sum_qty;
}
