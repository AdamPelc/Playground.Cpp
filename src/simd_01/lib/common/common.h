#pragma once

#include <new>
#include <vector>

// Workaround for clang
// clang++ V22.1.4 does not support <stdfloat>
template<typename T>
concept float32_c = std::numeric_limits<T>::is_iec559 &&
                    std::numeric_limits<T>::digits == 24 &&
                    std::numeric_limits<T>::max_exponent == 128 &&
                    sizeof(T) == 4;
static_assert(float32_c<float>);

struct order_book_t {
    std::vector<float> m_prices;
    std::vector<float> m_quantities;
};
