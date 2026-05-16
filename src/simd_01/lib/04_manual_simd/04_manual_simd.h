#pragma once

#include "common.h"

[[nodiscard]] float calculate_vwap_manual_simd(const order_book_t& order_book) noexcept;
