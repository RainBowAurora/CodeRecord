#ifndef __GTEST_ASSERT_H__
#define __GTEST_ASSERT_H__

#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace {

template<typename T>
T add(const T& a, const T& b){
    return a + b;
}

// 利用TEST()宏来定义命名一个测试第一个变量名是测试集的名字，
// 第二个变量名是测试集中某个测试的名字。不同测试集中的测试可以有相同的名字
TEST(GeneralTest, BasicAssertion){
    ASSERT_TRUE(add(1, 2) == 3);
    ASSERT_FALSE(add(1, 2) == 2);
}

TEST(GeneralTest, BinaryComparison){
    EXPECT_EQ(add(1,2), add(2, 1));
    EXPECT_GT(add(1,2), 1);
    EXPECT_NE(std::string("a"), std::string("b"));
    EXPECT_EQ(std::string("a"), std::string("a"));
    EXPECT_EQ(std::string("a"), "a"); 
    EXPECT_NE(std::string("a"), "b");
    {
        const char* c_str1 = "abc";
        const char* c_str2 = "abc";
        EXPECT_EQ(c_str1, c_str2); 
    }
    {
        const char* cstr_1 = "abc";
        const std::string stdstr = "abc";
        const char* cstr_2 = stdstr.c_str();
        // 反直觉，所以不要用EXPECT_NE做c string的比较
        EXPECT_NE(cstr_1, cstr_2);
    }
}

TEST(GeneralTest, StringComparison){
  const char* cstr_1 = "abc";
  const std::string stdstr_1 = "abc";
  const char* cstr_2 = stdstr_1.c_str();
  const std::string stdstr_2 = "AbC";
  const char* cstr_3 = stdstr_2.c_str();

  ASSERT_STREQ(cstr_1,cstr_2);
  ASSERT_STRCASEEQ(cstr_2,cstr_3);
  // ASSERT_STRCASEEQ(stdstr_1,stdstr_2); compile error.
}

TEST(GeneralTest, ThrowAssertion)
{
  const auto throw_error_lamba = [](){
    throw std::runtime_error("woops!");
  };
  ASSERT_THROW(throw_error_lamba(), std::runtime_error);
  ASSERT_ANY_THROW(throw_error_lamba());
  // 可以直接使用代码块
  ASSERT_NO_THROW({
    int a = 1;
  });
}

TEST(GeneralTest, FloatAssertion)
{
  ASSERT_FLOAT_EQ(1.0000001f, 1.0f);
  // double型的浮点数密度高，1e-7在4ULP以外
  // ASSERT_DOUBLE_EQ(1.0000001, 1.0); 失败
  ASSERT_NEAR(1.009f,1.0f,0.01f);
  // 谓词逻辑
  EXPECT_PRED_FORMAT2(::testing::FloatLE, 1.0000001f, 1.0f);
}

TEST(GeneralTest, GMockMatcher)
{
  const std::string str("Hello 123 world!");
  EXPECT_THAT(str, ::testing::StartsWith("Hello"));
  EXPECT_THAT(str, ::testing::EndsWith("world!"));
  ASSERT_THAT(str, ::testing::HasSubstr("llo"));
  EXPECT_THAT(str, ::testing::MatchesRegex(".*[1-9]{3}.*"));
}

bool equal(int m, int n)
{
  return m==n;
}

// A predicate-formatter for asserting that two integers are equal
testing::AssertionResult AssertEqual(const char* m_expr,
                                     const char* n_expr,
                                     int m,
                                     int n) {
  if (equal(m, n)) return testing::AssertionSuccess();

  return testing::AssertionFailure() << m_expr << " and " << n_expr
      << " (" << m << " and " << n << ") are not equal, "
      << "as they are " << m-n << " apart.";
}

TEST(GeneralTest, PredAssertion)
{
  const int m = 1;
  const int n = 1;
  EXPECT_PRED2(equal, m, n);
  EXPECT_PRED_FORMAT2(AssertEqual, m, n);
}
}

#endif /*__GTEST_ASSERT_H__*/