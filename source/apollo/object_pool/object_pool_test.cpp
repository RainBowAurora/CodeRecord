#include "object_pool.hpp"
#include <gtest/gtest.h>

struct TestNode
{
    TestNode():inited(true) { }
    ~TestNode() {
        inited = false;
        int value = 1;
    }

    explicit TestNode(int data) : value(data), inited(true) {}

    int value = 0;
    bool inited = false;
};

TEST(ObjectPoolTest, get_object){
    auto pool = std::make_shared<ObjectPool<TestNode>>(100, 10);
    for(int i = 0; i < 10; i++){
        EXPECT_EQ(10, pool->GetObject()->value);
    }

    EXPECT_NE(nullptr, pool->GetObject());
    pool.reset();


    auto pool2 = std::make_shared<ObjectPool<TestNode>>(10);
    for(int i = 0; i < 10; i++){
        EXPECT_EQ(0, pool2->GetObject()->value);
    }

    EXPECT_NE(nullptr, pool2->GetObject());
    pool2.reset();
}


int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}