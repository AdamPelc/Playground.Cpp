#include "02_vector_no_fast_math.h"

#include <gtest/gtest.h>

TEST(VectorNoFastMath, empty) {
    const order_book_t ob{};
    ASSERT_FLOAT_EQ(calculate_vwap_vector_no_fast_math(ob), 0.0f);
}

TEST(VectorNoFastMath, single_level) {
    const order_book_t ob{.m_prices = {100.0f}, .m_quantities = {10.0f}};
    ASSERT_FLOAT_EQ(calculate_vwap_vector_no_fast_math(ob), 100.0f);
}

TEST(VectorNoFastMath, two_levels_equal_quantity) {
    const order_book_t ob{.m_prices = {100.0f, 200.0f}, .m_quantities = {5.0f, 5.0f}};
    ASSERT_FLOAT_EQ(calculate_vwap_vector_no_fast_math(ob), 150.0f);
}

TEST(VectorNoFastMath, two_levels_unequal_quantity) {
    const order_book_t ob{.m_prices = {100.0f, 200.0f}, .m_quantities = {1.0f, 3.0f}};
    ASSERT_FLOAT_EQ(calculate_vwap_vector_no_fast_math(ob), 175.0f);
}

TEST(VectorNoFastMath, all_zero_quantities) {
    const order_book_t ob{.m_prices = {100.0f, 200.0f}, .m_quantities = {0.0f, 0.0f}};
    ASSERT_FLOAT_EQ(calculate_vwap_vector_no_fast_math(ob), 0.0f);
}

TEST(VectorNoFastMath, multiple_levels) {
    const order_book_t ob{
        .m_prices     = {10.0f, 20.0f, 30.0f},
        .m_quantities = {100.0f, 50.0f, 25.0f}
    };
    const float expected = (10.0f * 100.0f + 20.0f * 50.0f + 30.0f * 25.0f) / 175.0f;
    ASSERT_FLOAT_EQ(calculate_vwap_vector_no_fast_math(ob), expected);
}
