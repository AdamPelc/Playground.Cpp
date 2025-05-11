#pragma once
#include <optional>
#include <shared_mutex>
#include <stack>

template<typename T>
class stack_optimize_mutex_t {
public:
    void push(T value);
    std::optional<T> pop();
    std::optional<T> top() const;
    void reset();
private:
    mutable std::shared_mutex m_mutex;
    std::stack<T> m_stack;
};

template<typename T>
void stack_optimize_mutex_t<T>::push(T value) {
    std::unique_lock lock(m_mutex);
    m_stack.push(value);
}

template<typename T>
std::optional<T> stack_optimize_mutex_t<T>::pop() {
    std::unique_lock lock(m_mutex);
    if (m_stack.empty()) {
        return {};
    }
    auto value = m_stack.top();
    m_stack.pop();
    return value;
}

template<typename T>
std::optional<T> stack_optimize_mutex_t<T>::top() const {
    std::shared_lock lock(m_mutex);
    if (m_stack.empty()) {
        return {};
    }
    return m_stack.top();
}

template<typename T>
void stack_optimize_mutex_t<T>::reset() {
    std::stack<T>().swap(m_stack);
}
