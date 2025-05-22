#include "spsc_queue.h"

#include <queue>
#include <gtest/gtest.h>

TEST(spsc_queue_test, get_front_element_from_empty_queue) {
    const auto queue = spsc_queue_t<int, impl::queue_mutex_t>();
    const auto result = queue.dequeue();

    ASSERT_EQ(result, std::nullopt);
}

TEST(spsc_queue_test, get_front_element_from_queue_with_single_element){
    auto queue = spsc_queue_t<int, impl::queue_mutex_t>();

    queue.enqueue(1);
    const auto result = queue.dequeue();

    ASSERT_EQ(result, 1);
}

TEST(spsc_queue_test, get_front_element_from_queue_with_multiple_elements) {
    auto queue = spsc_queue_t<int, impl::queue_mutex_t>();

    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    const auto result = queue.dequeue();

    ASSERT_EQ(result, 1);
}
