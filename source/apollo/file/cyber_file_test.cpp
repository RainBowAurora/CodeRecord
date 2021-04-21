#include <gtest/gtest.h>
#include "cyber_file.h"

using namespace common;

TEST(file, GetAbsolutePath){
    const std::string prefix = "apollo";
    const std::string relative_path = "file";
    const std::string result = prefix + "/" + relative_path;
    
    // "apollo" + "file"
    ASSERT_STREQ(GetAbsolutePath(prefix, relative_path).c_str(), result.c_str());
    // "apollo/" + file
    ASSERT_STREQ(GetAbsolutePath(prefix+"/", relative_path).c_str(), result.c_str());
    // prefix/file + ""
    ASSERT_STREQ(GetAbsolutePath(prefix+"/"+relative_path, "").c_str(), result.c_str());
    // "" + prefix/file
    ASSERT_STREQ(GetAbsolutePath("", prefix+"/"+relative_path).c_str(), result.c_str());
}

TEST(file, FileUtilsTest){
    EXPECT_TRUE(PathExists("./"));
    EXPECT_FALSE(PathExists("not_exits_file"));
    
    EXPECT_TRUE(DirectoryExists("./"));
    EXPECT_FALSE(DirectoryExists("not_exits_file"));

    std::string current_path = GetCurrentPath();
    EXPECT_TRUE(EnsureDirectory(current_path));
    EXPECT_TRUE(EnsureDirectory(current_path + "/1"));
    EXPECT_TRUE(EnsureDirectory(current_path + "/1/2"));
    EXPECT_TRUE(EnsureDirectory(current_path + "/1/2/3"));
    EXPECT_TRUE(EnsureDirectory(current_path + "/2"));

    EXPECT_TRUE(CopyFile("/proc/version", current_path+"/2/version.back"));
    EXPECT_TRUE(PathExists(current_path+"/2/version.back"));

    EXPECT_TRUE(RemoveAllFiles(current_path + "/2"));
    
    EXPECT_TRUE(DeleteFile(current_path + "/1"));
    EXPECT_TRUE(DeleteFile(current_path + "/2"));
}

TEST(file, GetContent){
    std::string result;
    ASSERT_TRUE(GetContent(std::string(__FILE__), &result));
    ASSERT_FALSE(result.empty());
}

TEST(file, PathExists){
    //Path detection
    EXPECT_TRUE(PathExists("./"));
    EXPECT_FALSE(PathExists("not_exits_file"));

    EXPECT_TRUE(DirectoryExists("./"));
    EXPECT_FALSE(DirectoryExists("not_exits_file"));
    EXPECT_FALSE(DirectoryExists("message.binary"));
}


TEST(file, Glob){
    EXPECT_FALSE(Glob("./*").empty()); //获取当前所有文件和目录
    EXPECT_FALSE(Glob("/usr/loc?l/*").empty()); //获取/usr/local/下的所有文件和目录
}


TEST(FileTest, ListSubPaths) {
    const auto root_subdirs = ListSubPaths("/", DT_DIR); //目录
    // Some common root subdirs should exist.
    EXPECT_NE(root_subdirs.end(),
            std::find(root_subdirs.begin(), root_subdirs.end(), "home"));
    EXPECT_NE(root_subdirs.end(),
            std::find(root_subdirs.begin(), root_subdirs.end(), "root")); 
      // Something shouldn't exist.
    EXPECT_EQ(root_subdirs.end(),
            std::find(root_subdirs.begin(), root_subdirs.end(), "impossible"));  

    const auto root_subfile = ListSubPaths("/usr/local/lib",DT_REG); //文件
    EXPECT_NE(root_subfile.end(),
            std::find(root_subfile.begin(), root_subfile.end(), "libgtest.a"));
    EXPECT_EQ(root_subfile.end(),
            std::find(root_subfile.begin(), root_subfile.end(), "impossible")); 
}

TEST(FileTest, GetAbsolutePath) {
  EXPECT_EQ("./xx.txt", GetAbsolutePath("", "./xx.txt"));
  EXPECT_EQ("/abc", GetAbsolutePath("/abc", ""));
  EXPECT_EQ("/home/work/xx.txt", GetAbsolutePath("/home/work", "xx.txt"));
  EXPECT_EQ("/home/work/xx.txt", GetAbsolutePath("/home/work/", "xx.txt"));
  EXPECT_EQ("/xx.txt", GetAbsolutePath("/home/work", "/xx.txt"));
  EXPECT_EQ("/home/work/./xx.txt", GetAbsolutePath("/home/work", "./xx.txt"));
}

TEST(FileTest, GetFileName) {
  EXPECT_EQ("xx.txt", GetFileName("xx.txt"));
  EXPECT_EQ("xx", GetFileName("./xx.txt", true));
  EXPECT_EQ("xx.txt", GetFileName("./xx.txt"));
  EXPECT_EQ("xx", GetFileName("./xx.txt", true));
  EXPECT_EQ(".txt", GetFileName("./.txt"));
  EXPECT_EQ("", GetFileName("./.txt", true));
  EXPECT_EQ("txt", GetFileName("/path/.to/txt"));
  EXPECT_EQ("txt", GetFileName("/path/.to/txt", true));
  EXPECT_EQ("", GetFileName("/path/to/"));
  EXPECT_EQ("", GetFileName("/path/to/", true));
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}