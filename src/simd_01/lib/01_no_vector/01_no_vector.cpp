#include "01_no_vector.h"

#include <ranges>

float calculate_vwap_no_vector(const order_book_t& order_book) noexcept
{
    if (const auto depth = std::size(order_book.m_prices); depth == 0) {
        return {};
    }

    auto sum_weighted = 0.0f;
    auto sum_quantity = 0.0f;
    for (const auto [price, quantity] : std::views::zip(order_book.m_prices, order_book.m_quantities)) {
        sum_weighted += price * quantity;
        sum_quantity += quantity;
    }

    if (sum_weighted == 0.0f) {
        return {};
    }

    return sum_weighted / sum_quantity;
}
