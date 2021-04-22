#ifndef __CHRONO_RATE_H__
#define __CHRONO_RATE_H__

#include <iostream>
#include "chrono_time.h"
#include "chrono_duration.h"

class Rate{
public:
    Rate() = default;
    ~Rate() = default;
    explicit Rate(double frequency);
    explicit Rate(uint64_t nanosecond);
    explicit Rate(const Duration& duration);

    void Sleep();
    void Reset();

    Duration CycleTime() const { return actual_cycle_time_; } 
    Duration ExpectedCycleTime() const {return expected_cycle_time_;}

private:
    Time start_;
    Duration expected_cycle_time_; //预期周期
    Duration actual_cycle_time_; //循环的实际周期
};

#endif /*__CHRONO_RATE_H__*/