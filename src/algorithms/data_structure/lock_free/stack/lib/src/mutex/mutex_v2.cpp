#include "mutex/mutex_v2.hpp"

void mutex_v2_t::lock() {
    while (m_is_unique_lock.test_and_set(std::memory_order_acquire)) {
    }
}

void mutex_v2_t::lock_shared() { lock(); }

void mutex_v2_t::unlock_shared() { unlock(); }

void mutex_v2_t::unlock() { m_is_unique_lock.clear(std::memory_order_release); }
