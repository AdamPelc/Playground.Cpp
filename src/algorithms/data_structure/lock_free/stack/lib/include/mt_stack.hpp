#pragma once
#include <assert.h>

#include <atomic>
#include <deque>
#include <optional>

struct stack_counters_t {
    int m_producer{};
    int m_consumer{};
};

[[nodiscard]] inline bool are_counters_equal(stack_counters_t& counters,
                                             const std::atomic<stack_counters_t>& common_counters) {
    if (counters.m_producer == counters.m_consumer) {
        return true;
    }
    counters = common_counters.load(std::memory_order_relaxed);
    return false;
}

template <typename T>
class mt_stack_t {
public:
    void push(T value);
    std::optional<T> top() const;
    void reset();

private:
    std::deque<T> m_deque;
    mutable std::atomic<stack_counters_t> m_counters;
};

template <typename T>
void mt_stack_t<T>::push(T value) {
    auto counters = m_counters.load(std::memory_order_relaxed);

    while (
        !are_counters_equal(counters, m_counters) ||
        !m_counters.compare_exchange_weak(counters, {counters.m_producer + 1, counters.m_consumer},
                                          std::memory_order_acquire, std::memory_order_relaxed)) {
    }

    counters.m_producer++;
    m_deque.push_back(value);

    m_counters.compare_exchange_strong(counters, {counters.m_producer, counters.m_consumer + 1},
                                       std::memory_order_release, std::memory_order_relaxed);
}

template <typename T>
std::optional<T> mt_stack_t<T>::top() const {
    auto counters = m_counters.load(std::memory_order_relaxed);

    if (counters.m_consumer == 0) {
        return {};
    }

    while (
        !are_counters_equal(counters, m_counters) ||
        !m_counters.compare_exchange_weak(counters, {counters.m_producer, counters.m_consumer - 1},
                                          std::memory_order_acquire, std::memory_order_relaxed)) {
    }

    counters.m_consumer--;
    const auto value = m_deque.back();

    m_counters.compare_exchange_strong(counters, {counters.m_producer, counters.m_consumer + 1},
                                       std::memory_order_release, std::memory_order_relaxed);

    return value;
}

template <typename T>
void mt_stack_t<T>::reset() {
    std::deque<T>().swap(m_deque);
    m_counters.store({0, 0});
}
