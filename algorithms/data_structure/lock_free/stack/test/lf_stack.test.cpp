#include "lf_stack.hpp"

#include <barrier>
#include <format>
#include <gtest/gtest.h>
#include <latch>
#include <thread>

TEST(lock_free_stack_test, basic) {
    ASSERT_TRUE(true);
}

TEST(lock_free_stack_test, push_pop) {
    lf_stack_t<int> stack;
    const auto number_of_cores = std::thread::hardware_concurrency();
    std::latch latch{number_of_cores};

    auto worker = [&stack, &latch]() {
        latch.arrive_and_wait();
        for (int i = 0; i < 100; ++i) {
            stack.push(10);
            stack.pop();
        }
    };

    std::vector<std::jthread> threads;
    threads.reserve(number_of_cores);
    for(auto i = 0U; i < number_of_cores; ++i) {
        threads.emplace_back(worker);
    }

    ASSERT_TRUE(stack.empty());
}
