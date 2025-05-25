#include "spsc_queue.h"

#include <queue>
#include <gtest/gtest.h>
#include <thread>
#include <latch>

#include "impl/queue_wip.hpp"

template<typename impl_T>
class spsc_queue_test : public ::testing::Test {};

using queue_types = ::testing::Types<
    spsc_queue_t<int, impl::queue_mutex_t>,
    spsc_queue_t<int, impl::queue_wip_t>>;
TYPED_TEST_SUITE(spsc_queue_test, queue_types);


TYPED_TEST(spsc_queue_test, get_front_element_from_empty_queue) {
    auto queue = TypeParam(1'000);

    const auto result = queue.try_dequeue();

    ASSERT_EQ(result, std::nullopt);
}

TYPED_TEST(spsc_queue_test, get_front_element_from_queue_with_single_element){
    auto queue = TypeParam(1'000);

    queue.enqueue(1);
    const auto result = queue.try_dequeue();

    ASSERT_EQ(result, 1);
}

TYPED_TEST(spsc_queue_test, get_front_element_from_queue_with_multiple_elements) {
    auto queue = TypeParam(1'000);

    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);

    ASSERT_EQ(queue.try_dequeue(), 1);
    ASSERT_EQ(queue.try_dequeue(), 2);
    ASSERT_EQ(queue.try_dequeue(), 3);
}

TYPED_TEST(spsc_queue_test, check_if_queue_is_empty) {
    auto queue = TypeParam(1'000);

    ASSERT_TRUE(queue.is_empty());
}

TYPED_TEST(spsc_queue_test, get_concurent_enqueue_and_dequeue) {
    auto queue = TypeParam(10'000);
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
