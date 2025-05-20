#pragma once

#include <deque>
#include <mutex>
#include <shared_mutex>
#include <optional>

#include "impl/queue_mutex.hpp"

template<typename type_T, typename container_T = std::deque<type_T>, typename impl_T = impl::queue_mutex_t<type_T, container_T>>
class spsc_queue_t {
public:
    [[nodiscard]] std::optional<type_T> front() const;

private:
    impl_T m_impl;
};

template<typename type_T, typename container_T, typename impl_T>
auto spsc_queue_t<type_T, container_T, impl_T>::front() const -> std::optional<type_T> {
    return m_impl.front();
}
