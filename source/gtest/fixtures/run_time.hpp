#ifndef __GTEST_RUN_TIME_H__
#define __GTEST_RUN_TIME_H__

#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

#include <gtest/gtest.h>

class RunTime: public testing::Test{
protected:
    void SetUp() override{
        begin_ = std::chrono::steady_clock::now();
    }

    void TearDown() override{    
        end_ = std::chrono::steady_clock::now();
        auto spend_time = std::chrono::duration<double>(end_ - begin_);
        std::cout << "spend_time: " << spend_time.count() << std::endl;
    }
    std::chrono::_V2::steady_clock::time_point begin_;
    std::chrono::_V2::steady_clock::time_point end_;
};


TEST_F(RunTime, sleeping){
    std::cout << "sleep: 100ms\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}


TEST_F(RunTime, vector_push_back){
    //Do something
    std::vector<int> vec(1);
    for(int i = 0; i < 1024; i++){
        vec.push_back(i);
    }
}

#endif /*__GTEST_RUN_TIME_H__*/