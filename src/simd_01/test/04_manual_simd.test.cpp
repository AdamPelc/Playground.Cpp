#include "04_manual_simd.h"

#include <gtest/gtest.h>

// The implementation reads 8 floats at a time with _mm256_loadu_ps; depths
// that are not a multiple of 8 would read past the end of the vector (UB).
// Tests are restricted to depth == 0 or depth % 8 == 0.

TEST(ManualSimd, empty) {
    const order_book_t ob{};
    ASSERT_FLOAT_EQ(calculate_vwap_manual_simd(ob), 0.0f);
}

TEST(ManualSimd, all_zero_quantities) {
    const order_book_t ob{
        .m_prices     = {100.0f, 200.0f, 300.0f, 400.0f, 500.0f, 600.0f, 700.0f, 800.0f},
        .m_quantities = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f}
    };
    ASSERT_FLOAT_EQ(calculate_vwap_manual_simd(ob), 0.0f);
}

TEST(ManualSimd, eight_levels_equal_quantity) {
    const order_book_t ob{
        .m_prices     = {10.0f, 20.0f, 30.0f, 40.0f, 50.0f, 60.0f, 70.0f, 80.0f},
        .m_quantities = {1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f}
    };
    ASSERT_FLOAT_EQ(calculate_vwap_manual_simd(ob), 45.0f);
}

TEST(ManualSimd, eight_levels_unequal_quantity) {
    // sum_weighted = 1*8 + 2*7 + 3*6 + 4*5 + 5*4 + 6*3 + 7*2 + 8*1 = 120
    // sum_qty      = 8+7+6+5+4+3+2+1 = 36
    const order_book_t ob{
        .m_prices     = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f},
        .m_quantities = {8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f}
    };
    ASSERT_FLOAT_EQ(calculate_vwap_manual_simd(ob), 120.0f / 36.0f);
}

TEST(ManualSimd, sixteen_levels_equal_quantity) {
    const order_book_t ob{
        .m_prices     = {10.0f, 20.0f, 30.0f, 40.0f, 50.0f, 60.0f, 70.0f, 80.0f,
                         10.0f, 20.0f, 30.0f, 40.0f, 50.0f, 60.0f, 70.0f, 80.0f},
        .m_quantities = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                         1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f}
    };
    ASSERT_FLOAT_EQ(calculate_vwap_manual_simd(ob), 45.0f);
}
