#include <gtest/gtest.h>
#include "atomic_hash_map.h"
#include <thread>
#include <mutex>

TEST(AtomicHashMapTest, int_int) {
    AtomicHashMap<int, int> map;
    int value = 0;
    for (int i = 0; i < 1000; i++) {
        map.Set(i,i);
        EXPECT_TRUE( map.Hash(i) );
        EXPECT_TRUE( map.Get(i, &value) );
        EXPECT_EQ(i, value);
    }

    for (int i = 0; i < 1000; i++) {
        map.Set(1000 - i, i);
        EXPECT_TRUE( map.Hash(1000 - i) );
        EXPECT_TRUE( map.Get(1000 - i, &value) );
        EXPECT_EQ(i, value) << "hello";
    }
}


TEST(AtomicHashMapTest, int_string){
    AtomicHashMap<int, std::string> map;
    std::string value = "";
    for (int i = 0; i < 1000; i++) {
        map.Set(i,std::to_string(i));
        EXPECT_TRUE( map.Hash(i) );
        EXPECT_TRUE( map.Get(i, &value) );
        EXPECT_EQ(i, std::stoi(value)); 
    }

    for (int i = 0; i < 1000; i++) {
        map.Set(1000 - i,std::to_string(i));
        EXPECT_TRUE(map.Hash(1000 - i));
        EXPECT_TRUE(map.Get(1000 - i, &value));
        EXPECT_EQ(i, std::stoi(value));
    }
}

std::mutex mt;
TEST(AtomicHashMapTest, mulit_thread){
    AtomicHashMap<int, std::string, 128> map;
    const int thread_num = 32;
    std::thread th[thread_num];
    volatile bool ready = false;
        for (int i = 0; i < thread_num; i++) {
            th[i] = std::thread([&, i]{
                while(!ready);
                for(int j = 0; j < thread_num * 1000; j++){
                auto j_str = std::to_string(j);
                    map.Set(j);
                    map.Set(j, j_str);
                    map.Set(j, std::move(std::to_string(j)));
                }
            });
        }
        ready = true;
        for(int i = 0; i < thread_num; i++){
            th[i].join();
        }

    std::string value("");
    for (int i = 1; i < thread_num * 1000; i++) {
        EXPECT_TRUE(map.Get(i, &value));
        EXPECT_EQ(std::to_string(i), value);
    }
    std::string* str = nullptr;
    EXPECT_TRUE(map.Get(0, &str));
    EXPECT_EQ("0", *str);

}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}