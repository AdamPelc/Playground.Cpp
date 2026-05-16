#include "03_vector_fast_math.h"

#include <gtest/gtest.h>

// The implementation uses [[assume(size % 8 == 0)]], so only depth == 0 or
// exact multiples of 8 are tested to avoid undefined behaviour.

TEST(VectorFastMath, empty) {
    const order_book_t ob{};
    ASSERT_FLOAT_EQ(calculate_vwap_vector_fast_math(ob), 0.0f);
}

TEST(VectorFastMath, eight_levels_equal_quantity) {
    const order_book_t ob{
        .m_prices     = {10.0f, 20.0f, 30.0f, 40.0f, 50.0f, 60.0f, 70.0f, 80.0f},
        .m_quantities = {1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f}
    };
    ASSERT_FLOAT_EQ(calculate_vwap_vector_fast_math(ob), 45.0f);
}

TEST(VectorFastMath, eight_levels_unequal_quantity) {
    // sum_weighted = 1*8 + 2*7 + 3*6 + 4*5 + 5*4 + 6*3 + 7*2 + 8*1 = 120
    // sum_qty      = 8+7+6+5+4+3+2+1 = 36
    const order_book_t ob{
        .m_prices     = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f},
        .m_quantities = {8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f}
    };
    ASSERT_FLOAT_EQ(calculate_vwap_vector_fast_math(ob), 120.0f / 36.0f);
}

TEST(VectorFastMath, all_zero_quantities_eight_levels) {
    const order_book_t ob{
        .m_prices     = {10.0f, 20.0f, 30.0f, 40.0f, 50.0f, 60.0f, 70.0f, 80.0f},
        .m_quantities = {0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f}
    };
    ASSERT_FLOAT_EQ(calculate_vwap_vector_fast_math(ob), 0.0f);
}
