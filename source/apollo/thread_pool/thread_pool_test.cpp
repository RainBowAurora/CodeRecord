#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "thread_pool.h"

TEST(thread_pool, add_test){
    std::mutex mtx;
    try
    {
        ThreadPool tp;
        std::vector<std::future<int>> v;
        std::vector<std::future<void>> v1;

        for (int i = 0; i <= 10; ++i)
        {
            auto ans = tp.add([](int answer) { return answer; }, i);
            v.push_back(std::move(ans));
        }
        for (int i = 0; i <= 5; ++i)
        {
            auto ans = tp.add([&mtx](const std::string& str1, const std::string& str2)
            {
                std::lock_guard<std::mutex> lg(mtx);
                return;
            }, "hello ", "world");
            v1.push_back(std::move(ans));
        }

        
        for (size_t i = 0; i < v.size(); ++i)
        {
            std::lock_guard<std::mutex> lg(mtx);
            EXPECT_EQ(v[i].get(), i);
        }
        
        for (size_t i = 0; i < v1.size(); ++i)
        {
            v1[i].get();
        }
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}