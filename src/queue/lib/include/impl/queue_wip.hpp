#pragma once

#include <atomic>
#include <cstdint>
#include <deque>
#include <optional>
#include <vector>

namespace impl {

template <typename type_T, typename container_T = std::deque<type_T>>
class queue_wip_t {
public:
    explicit queue_wip_t(std::size_t capacity);

    [[nodiscard]]
    auto try_dequeue() -> std::optional<type_T>;
    auto enqueue(type_T value) -> void;
    [[nodiscard]]
    auto is_empty() const -> bool;

private:
    alignas(64) std::size_t m_capacity{};
    alignas(64) std::unique_ptr<type_T[]> m_data;
    alignas(64) std::atomic_uint64_t m_head{};
    std::uint64_t m_cached_tail{};
    alignas(64) std::atomic_uint64_t m_tail{};
    std::uint64_t m_cached_head{};
};

template <typename type_T, typename container_T>
queue_wip_t<type_T, container_T>::queue_wip_t(const std::size_t capacity)
    : m_capacity(capacity), m_data(std::make_unique<type_T[]>(capacity)) {}

template <typename type_T, typename container_T>
auto queue_wip_t<type_T, container_T>::try_dequeue() -> std::optional<type_T> {
    const auto tail = m_tail.load(std::memory_order_relaxed);
    if (tail == m_cached_head) {  // is_empty()
        m_cached_head = m_head.load(std::memory_order_acquire);
        if (tail == m_cached_head) {  // is_still_empty()
            return {};
        }
    }

    const auto value = std::move(m_data[tail % m_capacity]);
    m_tail.fetch_add(1, std::memory_order_release);
    return value;
}

template <typename type_T, typename container_T>
auto queue_wip_t<type_T, container_T>::enqueue(type_T value) -> void {
    const auto head = m_head.load(std::memory_order_relaxed);
    if (head - m_cached_tail == m_capacity - 1) {
        m_cached_tail = m_tail.load(std::memory_order_acquire);
        if (head - m_cached_tail == m_capacity - 1) {
            return;
        }
    }
    m_data[head % m_capacity] = std::move(value);
    m_head.fetch_add(1, std::memory_order_release);
}

template <typename type_T, typename container_T>
auto queue_wip_t<type_T, container_T>::is_empty() const -> bool {
    auto head = m_head.load(std::memory_order_acquire);
    auto tail = m_tail.load(std::memory_order_acquire);
    if (head == tail) {
        return true;
    }
    return false;
}
}  // namespace impl
