#include "02_vector_no_fast_math.h"

#include <ranges>

float calculate_vwap_vector_no_fast_math(const order_book_t& order_book) noexcept
{
    if (const auto depth = std::size(order_book.m_prices); depth == 0) {
        return {};
    }

    auto sum_weighted = 0.0f;
    auto sum_quantity = 0.0f;
    for (auto idx = 0uz; idx != std::size(order_book.m_prices); ++idx) {
        const auto price = order_book.m_prices[idx];
        const auto quantity = order_book.m_quantities[idx];
        sum_weighted += price * quantity;
        sum_quantity += quantity;
    }

    if (sum_weighted == 0.0f) {
        return {};
    }

    return sum_weighted / sum_quantity;
}
