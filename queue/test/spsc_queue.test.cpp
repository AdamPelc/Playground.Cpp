#include "spsc_queue.h"

#include <gtest/gtest.h>

TEST(spsc_queue_test, pop_empty) {
    spsc_queue_t<int> queue;
    auto result = queue.pop();

    ASSERT_EQ(result, std::nullopt);
}
