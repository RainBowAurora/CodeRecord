#ifndef __RW_LOCK_GUARD_H__
#define __RW_LOCK_GUARD_H__
template <typename RWLock>
class ReadLockGuard{
public:
    explicit ReadLockGuard(RWLock& lock):rw_lock_(lock) { rw_lock_.ReadLock(); }
    ~ReadLockGuard() { rw_lock_.ReadUnLock(); }
private:
    RWLock& rw_lock_;
    ReadLockGuard(const ReadLockGuard&) = delete;
    ReadLockGuard& operator=(const ReadLockGuard&) = delete;
};


template <typename RWLock>
class WriteLockGuard{
public:
    explicit WriteLockGuard(RWLock & lock):rw_lock_(lock) { rw_lock_.WriteLock(); } 
    ~WriteLockGuard() { rw_lock_.WriteUnLock(); };
private:
    RWLock& rw_lock_;
    WriteLockGuard(const WriteLockGuard&) = delete;
    WriteLockGuard& operator=(const WriteLockGuard&) = delete;
};

#endif /*__RW_LOCK_GUARD_H__*/