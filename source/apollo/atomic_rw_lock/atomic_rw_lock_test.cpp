#include <iostream>
#include "atomic_rw_lock.h"
#include <gtest/gtest.h>

TEST(ReentrantRWLockTest, read_lock) {
  int count = 0;
  int thread_init = 0;
  bool flag = true;
  AtomicRWLock lock;
  auto f = [&]() {
    ReadLockGuard<AtomicRWLock> lg(lock);
    count++;
    thread_init++;
    while (flag) {
      std::this_thread::yield();
    }
  };
  std::thread t1(f);
  std::thread t2(f);
  while (thread_init != 2) {
    std::this_thread::yield();
  }
  EXPECT_EQ(2, count);
  flag = false;
  t1.join();
  t2.join();
  {
    ReadLockGuard<AtomicRWLock> lg1(lock);
    {
      ReadLockGuard<AtomicRWLock> lg2(lock);
      {
        ReadLockGuard<AtomicRWLock> lg3(lock);
        { ReadLockGuard<AtomicRWLock> lg4(lock); }
      }
    }
  }
}

TEST(ReentrantRWLockTest, write_lock) {
  int count = 0;
  int thread_run = 0;
  bool flag = true;
  AtomicRWLock lock(false);
  auto f = [&]() {
    thread_run++;
    WriteLockGuard<AtomicRWLock> lg(lock);
    count++;
    while (flag) {
      std::this_thread::yield();
    }
  };
  std::thread t1(f);
  std::thread t2(f);
  while (thread_run != 2) {
    std::this_thread::yield();
  }
  EXPECT_EQ(1, count);
  flag = false;
  t1.join();
  t2.join();
}


int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}