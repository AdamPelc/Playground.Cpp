#pragma once
#include <atomic>

class mutex_v2_t {
public:
    void lock();
    void lock_shared();
    void unlock_shared();
    void unlock();
private:
    std::atomic_flag m_is_unique_lock = {};
};
