#include <iostream>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "suffix_separation.h"

TEST(file_test ,suffix_separtion){
    std::vector<std::string> file_name1 = {"111",""};
    std::vector<std::string> file_name2 = {"file",".yml"};
    std::vector<std::string> file_name3 = {"file.",""};
    std::vector<std::string> file_name4 = {".gitignore",""};
    std::vector<std::string> file_name5 = {"file.txt",".out"};
    std::vector<std::string> file_name6 = {"文件名",".扩展名"};
    std::vector<std::string> file_name7 = {"C:\\dir\\fname",".ext"};
    std::vector<std::string> file_name8 = {"https://github",".com"};

    EXPECT_STREQ(std::get<0>(PathFindExtension(file_name1[0]+file_name1[1])).c_str(), 
                file_name1[0].c_str());
    EXPECT_STREQ(std::get<1>(PathFindExtension(file_name1[0]+file_name1[1])).c_str(), 
                file_name1[1].c_str());

    EXPECT_STREQ(std::get<0>(PathFindExtension(file_name2[0]+file_name2[1])).c_str(), 
                file_name2[0].c_str());
    EXPECT_STREQ(std::get<1>(PathFindExtension(file_name2[0]+file_name2[1])).c_str(), 
                file_name2[1].c_str());

    EXPECT_STREQ(std::get<0>(PathFindExtension(file_name3[0]+file_name3[1])).c_str(), 
                file_name3[0].c_str());
    EXPECT_STREQ(std::get<1>(PathFindExtension(file_name3[0]+file_name3[1])).c_str(), 
                file_name3[1].c_str());

    EXPECT_STREQ(std::get<0>(PathFindExtension(file_name4[0]+file_name4[1])).c_str(), 
                file_name4[0].c_str());
    EXPECT_STREQ(std::get<1>(PathFindExtension(file_name4[0]+file_name4[1])).c_str(), 
                file_name4[1].c_str());

    EXPECT_STREQ(std::get<0>(PathFindExtension(file_name5[0]+file_name5[1])).c_str(), 
                file_name5[0].c_str());
    EXPECT_STREQ(std::get<1>(PathFindExtension(file_name5[0]+file_name5[1])).c_str(), 
                file_name5[1].c_str());

    EXPECT_STREQ(std::get<0>(PathFindExtension(file_name6[0]+file_name6[1])).c_str(), 
                file_name6[0].c_str());
    EXPECT_STREQ(std::get<1>(PathFindExtension(file_name6[0]+file_name6[1])).c_str(), 
                file_name6[1].c_str());

    EXPECT_STREQ(std::get<0>(PathFindExtension(file_name7[0]+file_name7[1])).c_str(), 
                file_name7[0].c_str());
    EXPECT_STREQ(std::get<1>(PathFindExtension(file_name7[0]+file_name7[1])).c_str(), 
                file_name7[1].c_str());

    EXPECT_STREQ(std::get<0>(PathFindExtension(file_name8[0]+file_name8[1])).c_str(), 
                file_name8[0].c_str());
    EXPECT_STREQ(std::get<1>(PathFindExtension(file_name8[0]+file_name8[1])).c_str(), 
                file_name8[1].c_str());
}

TEST(file_test, get_current_file_name){
    EXPECT_STREQ(std::string(FILE_NAME).c_str(), "suffix_separation_test.cpp");
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}