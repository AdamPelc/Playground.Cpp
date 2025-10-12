#pragma once
#include <optional>
#include <shared_mutex>
#include <stack>

template<typename TData, typename TMutex = std::shared_mutex>
class stack_mutex_t {
public:
    void push(TData value);
    std::optional<TData> pop();
    std::optional<TData> top() const;
    void reset();
private:
    mutable TMutex m_mutex;
    std::stack<TData> m_stack;
};

template<typename TData, typename TMutex>
void stack_mutex_t<TData, TMutex>::push(TData value) {
    std::unique_lock lock(m_mutex);
    m_stack.push(value);
}

template<typename TData, typename TMutex>
std::optional<TData> stack_mutex_t<TData, TMutex>::pop() {
    std::unique_lock lock(m_mutex);
    if (m_stack.empty()) {
        return {};
    }
    auto value = m_stack.top();
    m_stack.pop();
    return value;
}

template<typename TData, typename TMutex>
std::optional<TData> stack_mutex_t<TData, TMutex>::top() const {
    std::shared_lock lock(m_mutex);
    if (m_stack.empty()) {
        return {};
    }
    return m_stack.top();
}

template<typename TData, typename TMutex>
void stack_mutex_t<TData, TMutex>::reset() {
    std::stack<TData>().swap(m_stack);
}
