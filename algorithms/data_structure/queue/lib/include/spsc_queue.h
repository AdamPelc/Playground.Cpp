#pragma once

#include <deque>
#include <mutex>
#include <shared_mutex>
#include <optional>

template<typename type_T, typename container_T = std::deque<type_T>>
class spsc_queue_t {
public:
    [[nodiscard]] std::optional<type_T> front() const;
    [[nodiscard]] std::optional<type_T> pop();
    void push(type_T value);

    [[nodiscard]] bool empty() const;

private:
    mutable std::mutex m_mutex;
    container_T m_container;
};

template<typename type_T, typename container_T>
auto spsc_queue_t<type_T, container_T>::front() const -> std::optional<type_T> {
    std::shared_lock lock(m_mutex);
    return m_container.front();
}

template<typename type_T, typename container_T>
auto spsc_queue_t<type_T, container_T>::pop() -> std::optional<type_T>{
    if(empty())
    {
        return {};
    }

    std::unique_lock lock(m_mutex);
    const auto value = std::move(m_container.front());
    m_container.pop_front();
    return value;
}

template<typename type_T, typename container_T>
void spsc_queue_t<type_T, container_T>::push( type_T value ) {
    std::unique_lock lock(m_mutex);
    m_container.push_back(value);
}

template<typename type_T, typename container_T>
bool spsc_queue_t<type_T, container_T>::empty() const {
    return m_container.empty();
}
