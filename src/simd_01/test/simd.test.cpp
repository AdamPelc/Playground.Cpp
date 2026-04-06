#include "simd.h"

#include <gtest/gtest.h>

using namespace simd_01;

TEST(get_vwap, empty_order_book) {
    const order_book_t order_book{};
    const auto vwap = get_vwap(order_book);

    ASSERT_EQ(vwap, 0);
}

TEST(get_vwap, single_level) {
    const order_book_t order_book{.m_prices = {100.0}, .m_quantities = {10}, .m_depth = 1};
    const auto vwap = get_vwap(order_book);

    ASSERT_DOUBLE_EQ(vwap, 100.0);
}

TEST(get_vwap, two_levels_equal_quantity) {
    const order_book_t order_book{
        .m_prices = {100.0, 200.0}, .m_quantities = {5, 5}, .m_depth = 2};
    const auto vwap = get_vwap(order_book);

    ASSERT_DOUBLE_EQ(vwap, 150.0);
}

TEST(get_vwap, two_levels_unequal_quantity) {
    const order_book_t order_book{
        .m_prices = {100.0, 200.0}, .m_quantities = {1, 3}, .m_depth = 2};
    const auto vwap = get_vwap(order_book);

    ASSERT_DOUBLE_EQ(vwap, 175.0);
}

TEST(get_vwap, all_zero_quantities) {
    const order_book_t order_book{
        .m_prices = {100.0, 200.0}, .m_quantities = {0, 0}, .m_depth = 2};
    const auto vwap = get_vwap(order_book);

    ASSERT_DOUBLE_EQ(vwap, 0.0);
}

TEST(get_vwap, multiple_levels) {
    const order_book_t order_book{
        .m_prices = {10.0, 20.0, 30.0}, .m_quantities = {100, 50, 25}, .m_depth = 3};
    const auto vwap = get_vwap(order_book);

    ASSERT_DOUBLE_EQ(vwap, 2750.0 / 175.0);
}

TEST(get_vwap_unrolled, empty_order_book) {
    const order_book_t order_book{};
    const auto vwap = get_vwap_unrolled(order_book);

    ASSERT_EQ(vwap, 0);
}

TEST(get_vwap_unrolled, single_level) {
    const order_book_t order_book{.m_prices = {100.0}, .m_quantities = {10.0}, .m_depth = 1};
    const auto vwap = get_vwap_unrolled(order_book);

    ASSERT_DOUBLE_EQ(vwap, 100.0);
}

TEST(get_vwap_unrolled, two_levels_unequal_quantity) {
    const order_book_t order_book{
        .m_prices = {100.0, 200.0}, .m_quantities = {1.0, 3.0}, .m_depth = 2};
    const auto vwap = get_vwap_unrolled(order_book);

    ASSERT_DOUBLE_EQ(vwap, 175.0);
}

TEST(get_vwap_unrolled, exactly_four_levels) {
    const order_book_t order_book{
        .m_prices = {10.0, 20.0, 30.0, 40.0}, .m_quantities = {1.0, 2.0, 3.0, 4.0}, .m_depth = 4};
    const auto vwap = get_vwap_unrolled(order_book);

    ASSERT_DOUBLE_EQ(vwap, 30.0);
}

TEST(get_vwap_unrolled, five_levels) {
    const order_book_t order_book{.m_prices = {10.0, 20.0, 30.0, 40.0, 50.0},
                                  .m_quantities = {1.0, 1.0, 1.0, 1.0, 1.0},
                                  .m_depth = 5};
    const auto vwap = get_vwap_unrolled(order_book);

    ASSERT_DOUBLE_EQ(vwap, 30.0);
}

TEST(get_vwap_unrolled, all_zero_quantities) {
    const order_book_t order_book{
        .m_prices = {100.0, 200.0}, .m_quantities = {0.0, 0.0}, .m_depth = 2};
    const auto vwap = get_vwap_unrolled(order_book);

    ASSERT_DOUBLE_EQ(vwap, 0.0);
}

TEST(get_vwap_avx2, empty_order_book) {
    const order_book_t order_book{};
    const auto vwap = get_vwap_avx2(order_book);

    ASSERT_EQ(vwap, 0);
}

TEST(get_vwap_avx2, exactly_four_levels) {
    const order_book_t order_book{
        .m_prices = {10.0, 20.0, 30.0, 40.0}, .m_quantities = {1.0, 2.0, 3.0, 4.0}, .m_depth = 4};
    const auto vwap = get_vwap_avx2(order_book);

    ASSERT_DOUBLE_EQ(vwap, 30.0);
}

TEST(get_vwap_avx2, eight_levels) {
    const order_book_t order_book{.m_prices = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0},
                                  .m_quantities = {8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0},
                                  .m_depth = 8};
    const auto vwap = get_vwap_avx2(order_book);

    ASSERT_DOUBLE_EQ(vwap, 120.0 / 36.0);
}