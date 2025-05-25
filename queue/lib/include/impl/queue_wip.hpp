#pragma once

#include <atomic>
#include <cstdint>
#include <deque>
#include <optional>
#include <vector>

namespace impl {

    template<typename type_T, typename container_T = std::deque<type_T>>
    class queue_wip_t {
    public:
        explicit queue_wip_t(std::size_t capacity);

        [[nodiscard]]
        auto try_dequeue() -> std::optional<type_T>;
        auto enqueue(type_T value) -> void;
        [[nodiscard]]
        auto is_empty() const -> bool;
    private:
        std::size_t m_capacity{};
        std::unique_ptr<type_T[]> m_data;
        std::uint64_t m_head{};
        std::uint64_t m_tail{};
        std::atomic<std::size_t> m_size{};
    };

    template<typename type_T, typename container_T>
    queue_wip_t<type_T, container_T>::queue_wip_t(const std::size_t capacity)
        : m_capacity(capacity)
        , m_data(std::make_unique<type_T[]>(capacity)) {}

    template<typename type_T, typename container_T>
    auto queue_wip_t<type_T, container_T>::try_dequeue() -> std::optional<type_T> {
        const auto size = m_size.load(std::memory_order_acquire);
        if (size == 0) {
            return {};
        }

        const auto value = std::move(m_data[m_tail]);
        ++m_tail;
        if (m_tail == m_capacity) {
            // TODO: Check if module operation will be faster
            m_tail = 0;
        }
        m_size.fetch_sub(1, std::memory_order_release);
        return value;
    }

    template<typename type_T, typename container_T>
    auto queue_wip_t<type_T, container_T>::enqueue(type_T value) -> void {
        const auto size = m_size.load(std::memory_order_acquire);
        if (size == m_capacity) {
            return;
        }

        m_data[m_head] = std::move(value); // TODO: Probably can perform std::move here.
        ++m_head;
        if (m_head == m_capacity) {
            m_head = 0;
        }

        m_size.fetch_add(1, std::memory_order_release);
    }

    template<typename type_T, typename container_T>
    auto queue_wip_t<type_T, container_T>::is_empty() const -> bool {
        return m_size.load(std::memory_order_relaxed) == 0;
    }
}
