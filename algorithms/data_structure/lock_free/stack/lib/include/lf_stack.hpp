#pragma once

#include <mutex>
#include <shared_mutex>
#include <stack>

template<typename TType>
class lf_stack_t {
public:
    void push(TType value);
    TType pop();
    TType top();
    bool empty();
private:
    mutable std::mutex m_mutex;
    std::stack<TType> m_stack;
};

template<typename TType>
void lf_stack_t<TType>::push(TType value) {
    std::unique_lock lock(m_mutex);
    m_stack.push(value);
}

template<typename TType>
TType lf_stack_t<TType>::pop() {
    std::unique_lock lock(m_mutex);
    auto value = m_stack.top();
    m_stack.pop();
    return value;
}

template<typename TType>
TType lf_stack_t<TType>::top() {
    std::unique_lock lock(m_mutex);
    return m_stack.top();
}

template<typename TType>
bool lf_stack_t<TType>::empty() {
    std::unique_lock lock(m_mutex);
    return m_stack.empty();
}
