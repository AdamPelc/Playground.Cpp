#pragma once

#include "impl/queue_mutex.hpp"

#include <deque>
#include <mutex>
#include <shared_mutex>
#include <optional>

// Few notes about single producer single consumer queue. During desing phase there are few things to consider:
// 1. Can it have fixed size?
// - Yes, circular buffer can be used.
// - No, than process of reallocation has to be locked on both threads.
// For circular buffer power of two can be used to reduce number of operations. Since, mask can be applied to recuse about
// of bits for index calculation.

template<
    typename type_T,
    template<typename, typename> class impl_T = impl::queue_mutex_t,
    template<typename> class container_T = std::deque>
class spsc_queue_t {
public:
    explicit spsc_queue_t(std::size_t capacity);
    [[nodiscard]]
    auto try_dequeue() -> std::optional<type_T>;

    auto enqueue(type_T value) -> void;

    [[nodiscard]]
    auto is_empty() const -> bool;

private:
    impl_T<type_T, container_T<type_T>> m_impl;
};

template<typename type_T, template <typename, typename> class impl_T, template <typename> class container_T>
spsc_queue_t<type_T, impl_T, container_T>::spsc_queue_t(std::size_t capacity) : m_impl(capacity) {}

template<
    typename type_T,
    template<typename, typename> class impl_T,
    template<typename> class container_T>
auto spsc_queue_t<type_T, impl_T, container_T>::try_dequeue() -> std::optional<type_T> {
    return m_impl.try_dequeue();
}

template<typename type_T, template <typename, typename> class impl_T, template <typename> class container_T>
auto spsc_queue_t<type_T, impl_T, container_T>::enqueue(type_T value) -> void {
    m_impl.enqueue(value);
}

template<typename type_T, template <typename, typename> class impl_T, template <typename> class container_T>
auto spsc_queue_t<type_T, impl_T, container_T>::is_empty() const -> bool {
    return m_impl.is_empty();
}
