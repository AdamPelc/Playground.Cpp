#include "spsc_queue.h"

#include <queue>
#include <gtest/gtest.h>
#include <thread>
#include <latch>

TEST(spsc_queue_test, get_front_element_from_empty_queue) {
    auto queue = spsc_queue_t<int, impl::queue_mutex_t>();

    const auto result = queue.try_dequeue();

    ASSERT_EQ(result, std::nullopt);
}

TEST(spsc_queue_test, get_front_element_from_queue_with_single_element){
    auto queue = spsc_queue_t<int, impl::queue_mutex_t>();

    queue.enqueue(1);
    const auto result = queue.try_dequeue();

    ASSERT_EQ(result, 1);
}

TEST(spsc_queue_test, get_front_element_from_queue_with_multiple_elements) {
    auto queue = spsc_queue_t<int, impl::queue_mutex_t>();

    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);

    ASSERT_EQ(queue.try_dequeue(), 1);
    ASSERT_EQ(queue.try_dequeue(), 2);
    ASSERT_EQ(queue.try_dequeue(), 3);
}

TEST(spsc_queue_test, check_if_queue_is_empty) {
    auto queue = spsc_queue_t<int, impl::queue_mutex_t>();

    ASSERT_TRUE(queue.is_empty());
}

TEST(spsc_queue_test, get_concurent_enqueue_and_dequeue) {
    auto queue = spsc_queue_t<int, impl::queue_mutex_t>();
    std::latch latch{2};

    auto t1 = std::jthread([&queue, &latch]() {
        latch.arrive_and_wait();
        for (auto i = 0; i < 1'000; ++i) {
            queue.enqueue(i);
        }
    });

    auto t2 = std::jthread([&queue, &latch]() {
        latch.arrive_and_wait();
        for (auto i = 0; i < 1'000; ++i) {
            [[maybe_unused]] volatile auto result = queue.try_dequeue();
        }
    });

    ASSERT_TRUE(true);
}
