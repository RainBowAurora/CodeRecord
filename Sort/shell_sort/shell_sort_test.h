#ifndef __SHELL_SORT_TEST_H__
#define __SHELL_SORT_TEST_H__

#include <gtest/gtest.h>
#include "shell_sort.h"

TEST(shell_sort_test, c_array){
    int data1[10]={1,2,3,4,5,6,7,8,9,10};
    int data2[10]={10,9,8,7,6,5,4,3,2,1};
    int data3[10]={5,5,5,5,5,4,4,4,4,4};
    int data4[1]={5};
    int comparedata1[10]={1,2,3,4,5,6,7,8,9,10};
    int comparedata2[10]={10,9,8,7,6,5,4,3,2,1};
    int comparedata3[10]={5,5,5,5,5,4,4,4,4,4};
    int comparedata4[1]={5}; 

    std::sort(comparedata1, comparedata1+10);
    ShellSort(data1, data1+10);
    std::sort(comparedata2, comparedata2+10);
    ShellSort(data2, data2+10);
    std::sort(comparedata3, comparedata3+10);
    ShellSort(data3, data3+10);
    std::sort(comparedata4, comparedata4+1);
    ShellSort(data4, data4+1);

    EXPECT_EQ(std::vector<int>(comparedata1, comparedata1+10), std::vector<int>(data1, data1+10));
    EXPECT_EQ(std::vector<int>(comparedata2, comparedata2+10), std::vector<int>(data2, data2+10));
    EXPECT_EQ(std::vector<int>(comparedata3, comparedata3+10), std::vector<int>(data3, data3+10));
    EXPECT_EQ(std::vector<int>(comparedata4, comparedata4+1), std::vector<int>(data4, data4+1));
}

TEST(shell_sort_test, stl_vector){
    std::vector<int> data1={1,2,3,4,5,6,7,8,9,10};
    std::vector<int> data2={10,9,8,7,6,5,4,3,2,1};
    std::vector<int> data3={5,5,5,5,5,4,4,4,4,4};
    std::vector<int> data4={5};
    std::vector<int> comparedata1={1,2,3,4,5,6,7,8,9,10};
    std::vector<int> comparedata2={10,9,8,7,6,5,4,3,2,1};
    std::vector<int> comparedata3={5,5,5,5,5,4,4,4,4,4};
    std::vector<int> comparedata4={5};

    std::sort(comparedata1.begin(), comparedata1.end());
    ShellSort(data1.begin(), data1.end());
    std::sort(comparedata2.begin(), comparedata2.end());
    ShellSort(data2.begin(), data2.end());
    std::sort(comparedata3.begin(), comparedata3.end());
    ShellSort(data3.begin(), data3.end());
    std::sort(comparedata4.begin(), comparedata4.end());
    ShellSort(data4.begin(), data4.end());

    EXPECT_EQ(comparedata1, data1);
    EXPECT_EQ(comparedata2, data2);
    EXPECT_EQ(comparedata3, data3);
    EXPECT_EQ(comparedata4, data4);
}

#endif /*__SHELL_SORT_TEST_H__*/