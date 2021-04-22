#ifndef __CHRONO_DURATION_H__
#define __CHRONO_DURATION_H__

#include <iostream>
#include <gtest/gtest.h>

#include "chrono_duration.h"

TEST(Duration, constructor) {
    Duration duration(100);
    EXPECT_EQ(100, duration.ToNanosecond());

    duration = Duration(1.1);
    EXPECT_EQ(1100000000UL, duration.ToNanosecond());
    EXPECT_DOUBLE_EQ(1.1, duration.ToSecond());

    duration = Duration(1, 1);
    EXPECT_EQ(1000000001UL, duration.ToNanosecond());
    EXPECT_DOUBLE_EQ(1.000000001, duration.ToSecond());

    Duration d2(duration);
    EXPECT_EQ(duration, d2);

    Duration d3;
    EXPECT_TRUE(d3.IsZero());
}

TEST(Duration, operators){
    Duration d1(100);
    Duration d2(200);
    Duration d3(300);

    EXPECT_NE(d1, d3); // d1 != d3
    EXPECT_LT(d1, d3); //d1 < d3
    EXPECT_LE(d1, d3); //d1 <= d3
    EXPECT_GT(d3, d1); //d3 > d1
    EXPECT_GE(d3, d1); //d3 >= d1

    EXPECT_EQ(-100, -d1.ToNanosecond()); 
    EXPECT_EQ(d1+d2, d3); //d1+d2 == d3
    EXPECT_EQ(d1*2, d2); //d1*2 == d2
    EXPECT_EQ(d3-d2, d1); //d3-d2 == d1
    EXPECT_EQ(d1+=d2, d3); //(d1+= d2)== d3
    EXPECT_EQ(Duration(100), d1 -= d2); 
    EXPECT_EQ(d2, d1 *= 2); 
}


#endif /*__CHRONO_DURATION_H__*/