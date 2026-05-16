#include <ranges>

#include "03_vector_fast_math.h"

float calculate_vwap_vector_fast_math(const order_book_t& order_book) noexcept
{
    if (const auto depth = std::size(order_book.m_prices); depth == 0) {
        return {};
    }

    auto sum_weighted = 0.0f;
    auto sum_quantity = 0.0f;
    const auto size = static_cast<int>(std::size(order_book.m_prices));
    [[assume(size % 8 == 0)]];
    for (auto idx = 0; idx != size; ++idx) {
        const auto i = static_cast<std::size_t>(idx);
        const auto price = order_book.m_prices[i];
        const auto quantity = order_book.m_quantities[i];
        sum_weighted += price * quantity;
        sum_quantity += quantity;
    }

    if (sum_weighted == 0.0f) {
        return {};
    }

    return sum_weighted / sum_quantity;
}
