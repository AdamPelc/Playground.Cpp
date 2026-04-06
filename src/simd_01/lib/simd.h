#pragma once

#include <cstdint>
#include <stdfloat>
#include <vector>

namespace simd_01 {

inline constexpr std::size_t cache_line_size = 64;

struct order_book_t {
    alignas(cache_line_size) std::vector<std::float64_t> m_prices;
    alignas(cache_line_size) std::vector<std::float64_t> m_quantities;
    alignas(cache_line_size) std::uint64_t m_depth;
};

[[nodiscard]] std::float64_t get_vwap(const order_book_t& order_book) noexcept;
[[nodiscard]] std::float64_t get_vwap_opt(const order_book_t& order_book) noexcept;
[[nodiscard]] std::float64_t get_vwap_unrolled(const order_book_t& order_book) noexcept;
[[nodiscard]] std::float64_t get_vwap_avx2(const order_book_t& order_book) noexcept;

}