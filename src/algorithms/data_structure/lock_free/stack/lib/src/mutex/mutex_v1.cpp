#include "mutex/mutex_v1.hpp"

void mutex_v1_t::lock() {
    // As long as the flag is set, it means that the lock is acquired
    while (m_is_unique_lock.test_and_set(std::memory_order_acquire)) {
        // If flag is set, wait for it to be cleared
        m_is_unique_lock.wait(true, std::memory_order_relaxed);
    }
}

void mutex_v1_t::lock_shared() {
    lock();
}

void mutex_v1_t::unlock_shared() {
    unlock();
}

void mutex_v1_t::unlock() {
    m_is_unique_lock.clear(std::memory_order_release);
    m_is_unique_lock.notify_one();
}
