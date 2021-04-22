#include <iostream>
#include "chrono_rate.h"

Rate::Rate(double frequency): 
    start_(Time::Now()),
    expected_cycle_time_(1.0 / frequency),
    actual_cycle_time_(0.0) {}

Rate::Rate(uint64_t nanosecond):
    start_(Time::Now()),
    expected_cycle_time_(static_cast<int64_t>(nanosecond)),
    actual_cycle_time_(0.0) {}

Rate::Rate(const Duration& duration):
    start_(Time::Now()), 
    expected_cycle_time_(duration), 
    actual_cycle_time_(0.0) {}

void Rate::Sleep()
{
    Time expected_end = start_ + expected_cycle_time_;
    Time actual_end = Time::Now();
    //检测时间的向后跳跃
    if (actual_end < start_) {
        std::cout << "[WARN] Detect backward jumps in time";
        expected_end = actual_end + expected_cycle_time_;   
    }

    // 计算我们要sleep的周期
    Duration sleep_time = expected_end - actual_end;
    //设置循环的实际周期
    actual_cycle_time_ = actual_end - start_; 

    //确保重置我们的开始时间
    start_ = expected_end;

    if (sleep_time < Duration(0.0)) {
        std::cout << "[WARN] Detect forward jumps in time"; 
        if (actual_end > expected_end + expected_cycle_time_) {
            start_ = actual_end;
        }
        return;
    }

    Time::SleepUntil(expected_end);
}

void Rate::Reset()
{
    start_ = Time::Now();
}
