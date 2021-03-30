#ifndef __ATOMIC_RW_LOCK_H__
#define __ATOMIC_RW_LOCK_H__

#include <iostream>
#include <atomic>
#include <chrono>
#include <thread>
#include "rw_lock_guard.h"


class AtomicRWLock{
public:
    friend ReadLockGuard<AtomicRWLock>;
    friend WriteLockGuard<AtomicRWLock>;
    
    static const int32_t RW_LOCK_FREE = 0;
    static const int32_t WRITE_EXCLUSIVE = -1;
    static const int32_t MAX_RETRY_TIMES = 5;

    AtomicRWLock() = default;
    explicit AtomicRWLock(bool write_first):write_first_(write_first) { }


private:
    bool write_first_ = true;
    std::atomic<uint32_t> write_lock_wait_num_ = {0};
    std::atomic<int32_t> lock_num_ = {0};

    AtomicRWLock(const AtomicRWLock&) = delete;
    AtomicRWLock& operator=(const AtomicRWLock&) = delete;

    void ReadLock();
    void ReadUnLock();

    void WriteLock();
    void WriteUnLock();
};


void AtomicRWLock::ReadLock()
{
    uint32_t retry_times = 0;
    int32_t temp_lock_num = lock_num_.load();
    if(write_first_){
        do{
            while(temp_lock_num < RW_LOCK_FREE || write_lock_wait_num_.load() > 0 ){
                if(++retry_times == MAX_RETRY_TIMES){
                    std::this_thread::yield();
                    retry_times = 0;
                }
                temp_lock_num = lock_num_.load();
            }
        }while(!lock_num_.compare_exchange_strong(temp_lock_num, temp_lock_num + 1,
                                                std::memory_order_acq_rel, 
                                                std::memory_order_relaxed));
    }else{
        do{
            while(temp_lock_num < RW_LOCK_FREE){
                if(++retry_times == MAX_RETRY_TIMES){
                    std::this_thread::yield();
                    retry_times = 0;
                }
                temp_lock_num = lock_num_.load();
            }
        }while(!lock_num_.compare_exchange_strong(temp_lock_num, temp_lock_num + 1,
                                                std::memory_order_acq_rel,
                                                std::memory_order_relaxed));
    }
}

void AtomicRWLock::WriteLock()
{
    int32_t rw_lock_free = RW_LOCK_FREE;
    uint32_t retry_times = 0;
    write_lock_wait_num_.fetch_add(1);
    while(!lock_num_.compare_exchange_strong(rw_lock_free, WRITE_EXCLUSIVE,
                                            std::memory_order_acq_rel,
                                            std::memory_order_relaxed)){
        rw_lock_free = RW_LOCK_FREE;
        if(++retry_times == MAX_RETRY_TIMES){
            std::this_thread::yield();
            retry_times = 0;
        }
    }
    write_lock_wait_num_.fetch_sub(1);
}

void AtomicRWLock::ReadUnLock() { lock_num_.fetch_sub(1); }
void AtomicRWLock::WriteUnLock() { lock_num_.fetch_add(1); }

#endif /*__ATOMIC_RW_LOCK_H__*/