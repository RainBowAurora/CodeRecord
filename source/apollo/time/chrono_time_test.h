#ifndef __CHRONO_TIME_TEST_H__
#define __CHRONO_TIME_TEST_H__

#include <iostream>
#include <gtest/gtest.h>

#include "chrono_time.h"

TEST(chrono_time, constructor){
    Time time(100UL);
    EXPECT_EQ(100UL, time.ToNanosecond()); 

    time = Time(1.1);
    EXPECT_EQ(1100000000UL, time.ToNanosecond());   
    EXPECT_DOUBLE_EQ(1.1, time.ToSecond());

    time = Time(1, 1);
    EXPECT_EQ(1000000001UL, time.ToNanosecond());
    EXPECT_DOUBLE_EQ(1.000000001, time.ToSecond());

    Time time2(time);
    EXPECT_EQ(time2, time);
}

TEST(chrono_time, Now){
    std::cout << "Time Now: " << Time::Now() << std::endl;
}

TEST(chrono_time, IsZero)
{
    Time time;
    EXPECT_TRUE(time.IsZero());
    EXPECT_TRUE(Time::MIN.IsZero());
    EXPECT_FALSE(Time::MAX.IsZero());
}

TEST(chrono_time, to_string) {
  Time t1(1631227311223456789UL);
  std::cout << t1.ToString().c_str() << std::endl;
  Time t2(1531225311000006789UL);
  std::cout << t2.ToString().c_str() << std::endl;
}

TEST(chrono_time, Trigger){
    Time t1 = Time::Now();
    std::cout << "每天定点触发\n";  
    Duration duration(86400.0);
    for(int i = 0; i < 10; i++){
        t1+=duration;
        std::cout << t1.ToString() << std::endl;
    }
}


#endif /*__CHRONO_TIME_TEST_H__*/