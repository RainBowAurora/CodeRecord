#ifndef __GTEST_FIXTURES_H__
#define __GTEST_FIXTURES_H__

#include <iostream>
#include <queue>

#include <gtest/gtest.h>

class QueueTest: public ::testing::Test{
protected:
    void SetUp() override {
        std::cout << "SetUp\n";
        q0_.push(0);
        q1_.push(10086);
    }

    void TearDown() override{
        std::cout << "TearDown\n";
    }

    std::queue<int> q0_;
    std::queue<int> q1_;
};


TEST_F(QueueTest, fixtures1){
    ASSERT_EQ(q1_.front(), 10086);
    EXPECT_TRUE(q0_.size() == 1);
    q0_.pop();
    EXPECT_TRUE(q0_.empty());
}

TEST_F(QueueTest, fixtures2){
    // fixtures1 fixtures2 测试之间互不影响
    EXPECT_TRUE(q0_.size() == 1);
}

#endif /*__GTEST_FIXTURES_H__*/