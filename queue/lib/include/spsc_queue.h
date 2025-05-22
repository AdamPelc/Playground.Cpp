#pragma once

#include <deque>
#include <mutex>
#include <shared_mutex>
#include <optional>

#include "impl/queue_mutex.hpp"

template<
    typename type_T,
    template<typename, typename> class impl_T = impl::queue_mutex_t,
    template<typename> class container_T = std::deque>
class spsc_queue_t {
public:
    [[nodiscard]]
    auto dequeue() -> std::optional<type_T>;

    auto enqueue(type_T value) -> void;

    [[nodiscard]]
    auto is_empty() const -> bool;

private:
    impl_T<type_T, container_T<type_T>> m_impl;
};

template<
    typename type_T,
    template<typename, typename> class impl_T,
    template<typename> class container_T>
auto spsc_queue_t<type_T, impl_T, container_T>::dequeue() -> std::optional<type_T> {
    return m_impl.dequeue();
}

template<typename type_T, template <typename, typename> class impl_T, template <typename> class container_T>
auto spsc_queue_t<type_T, impl_T, container_T>::enqueue(type_T value) -> void {
    m_impl.enqueue(value);
}

template<typename type_T, template <typename, typename> class impl_T, template <typename> class container_T>
auto spsc_queue_t<type_T, impl_T, container_T>::is_empty() const -> bool {
    return m_impl.is_empty();
}
