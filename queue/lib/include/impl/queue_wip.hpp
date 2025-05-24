#pragma once

#include <atomic>
#include <cstdint>
#include <deque>
#include <optional>

namespace impl {

    template<typename type_T, typename container_T = std::deque<type_T>>
    class queue_wip_t {
    public:
        [[nodiscard]]
        auto try_dequeue() -> std::optional<type_T>;
        auto enqueue(type_T value) -> void;
        [[nodiscard]]
        auto is_empty() const -> bool;
    private:
        std::atomic<std::uint64_t> m_head = 0;
        std::atomic<std::uint64_t> m_tail = 0;
        container_T m_container;
    };

    template<typename type_T, typename container_T>
    auto queue_wip_t<type_T, container_T>::try_dequeue() -> std::optional<type_T> {
         if (is_empty()) {
             return {};
         }

        auto value = m_container.front();
        m_container.pop_front();
        m_head.fetch_add(1, std::memory_order_relaxed);
        return value;
    }

    template<typename type_T, typename container_T>
    auto queue_wip_t<type_T, container_T>::enqueue(type_T value) -> void {
        m_container.push_back(value);
        m_tail.fetch_add(1, std::memory_order_relaxed);
    }

    template<typename type_T, typename container_T>
    auto queue_wip_t<type_T, container_T>::is_empty() const -> bool {
        const auto head = m_head.load(std::memory_order_relaxed);
        const auto tail = m_tail.load(std::memory_order_relaxed);
        return head == tail;
    }
}
