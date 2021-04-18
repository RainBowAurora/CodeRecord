# GTest系列之断言

GTest提供的断言有致命(Fatal)和非致命(Non-fatal)两个版本。致命断言以`ASSERT_`打头，非致命断言以`EXPECT_`打头。致命断言报错时，单元测试**中止并返回**；非致命断言报错时程序**继续运行**，测试其他的断言。断言不局限于在单元测试时使用，任何返回值为void的函数都可以使用断言，具体的逻辑请见[此处](https://github.com/google/googletest/blob/master/googletest/docs/advanced.md#assertion-placement)。在GTest提供了一下几个类别的断言。

## 元断言
`SUCCESS()`和 `FAIL()`，`SUCCESS()`仅仅用作说明某件事成功，不代表单元测试成功，好像没什么用。FAIL()可以被用在控制逻辑中。
```
FAIL() << "Fatal Failure";
// 上述一行代码可以用来替代下面的两行代码。
std::cerr << "Fatal Failure" <<std::end;
exit(-1);
```

## 条件断言
条件断言判断条件是否为真，这里给出了致命和非致命的类型。接下来的断言只给出`ASSERT_xxx`形式,默认是有对应的`EXPECT_xxx`版本。
Fatal assertion            | Nonfatal assertion         | Verifies
-------------------------- | -------------------------- | --------------------
`ASSERT_TRUE(condition);`  | `EXPECT_TRUE(condition);`  | `condition` is true
`ASSERT_FALSE(condition);` | `EXPECT_FALSE(condition);` | `condition` is false

```
int add(int a, int b);
TEST(GeneralTest, BasicAssertion)
{
  ASSERT_TRUE(add(1, 2) == 3);

  ASSERT_FALSE(add(1, 2) == 2);
}
```
> 要提供自定义失败消息，只需使用<<操作符或此类操作符序列将其流式传输到宏中即可:
> `ASSERT_TRUE(add(1, 2) == 2) << "This test filed!!";`

## 二元比较
二元比较断言比较两个值的关系。这类段言假设 `==`,`<`等运算符在val1和val2上重载。当比较`C` `string(eg. const char*)`时，这类断言只做指针比较,这和直觉是相反的，请不要使用ASSERT_EQ等做C string的比较。

Fatal assertion          | Nonfatal assertion       | Verifies
------------------------ | ------------------------ | --------------
`ASSERT_EQ(val1, val2);` | `EXPECT_EQ(val1, val2);` | `val1 == val2`
`ASSERT_NE(val1, val2);` | `EXPECT_NE(val1, val2);` | `val1 != val2`
`ASSERT_LT(val1, val2);` | `EXPECT_LT(val1, val2);` | `val1 < val2`
`ASSERT_LE(val1, val2);` | `EXPECT_LE(val1, val2);` | `val1 <= val2`
`ASSERT_GT(val1, val2);` | `EXPECT_GT(val1, val2);` | `val1 > val2`
`ASSERT_GE(val1, val2);` | `EXPECT_GE(val1, val2);` | `val1 >= val2`

```
TEST(GeneralTest, BinaryComparison) {
  EXPECT_EQ(add(1,2), add(2, 1)); //1+2 == 2+1
  EXPECT_GT(add(1,2), 1); //1+2 > 1
  EXPECT_NE(std::string("a"), std::string("b")); 
  EXPECT_EQ(std::string("a"), std::string("a"));

  EXPECT_EQ(std::string("a"), "a"); 
  EXPECT_NE(std::string("a"), "b");

  {
    const char* cstr_1 = "abc";
    const char* cstr_2 = "abc";
    // 虽然两者相等，但是只是指针地址相等
    // a_cstr和b_cstr拥有相同的地址是因为编译器
    // 将相同的字符串常量放到了同一个常量区。
    EXPECT_EQ(cstr_1, cstr_2); 
  }
  {
    const char* cstr_1 = "abc";
    const std::string stdstr = "abc";
    const char* cstr_2 = stdstr.c_str();
    // 反直觉，所以不要用EXPECT_NE做c string的比较
    EXPECT_NE(cstr_1, cstr_2);
  }
}
```

## 字符串比较
这类断言是比较C 字符串的，如果想要比较`std::string`,请使用`ASSERT_EQ`和`ASSERT_NE`。
| Fatal assertion                | Nonfatal assertion             | Verifies                                                 |
| --------------------------     | ------------------------------ | -------------------------------------------------------- |
| `ASSERT_STREQ(str1,str2);`     | `EXPECT_STREQ(str1,str2);`     | the two C strings have the same content   		     |
| `ASSERT_STRNE(str1,str2);`     | `EXPECT_STRNE(str1,str2);`     | the two C strings have different contents 		     |
| `ASSERT_STRCASEEQ(str1,str2);` | `EXPECT_STRCASEEQ(str1,str2);` | the two C strings have the same content, ignoring case   |
| `ASSERT_STRCASENE(str1,str2);` | `EXPECT_STRCASENE(str1,str2);` | the two C strings have different contents, ignoring case |

```
TEST(GeneralTest, StringComparison)
{
  const char* cstr_1 = "abc";
  const std::string stdstr_1 = "abc";
  const char* cstr_2 = stdstr_1.c_str();
  const std::string stdstr_2 = "AbC";
  const char* cstr_3 = stdstr_2.c_str();

  ASSERT_STREQ(cstr_1,cstr_2); 
  ASSERT_STRCASEEQ(cstr_2,cstr_3); 
  // ASSERT_STRCASEEQ(stdstr_1,stdstr_2); compile error.
}
```

## 异常相关断言
这一系列断言检测是否有异常抛出和检查异常类型。


Fatal assertion                            | Nonfatal assertion                         | Verifies
------------------------------------------ | ------------------------------------------ | --------
`ASSERT_THROW(statement, exception_type);` | `EXPECT_THROW(statement, exception_type);` | `statement` throws an exception of the given type
`ASSERT_ANY_THROW(statement);`             | `EXPECT_ANY_THROW(statement);`             | `statement` throws an exception of any type
`ASSERT_NO_THROW(statement);`              | `EXPECT_NO_THROW(statement);`              | `statement` doesn't throw any exception

```
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
```
## 浮点数断言
浮点数因为round-off error，两个浮点数完全一样的可能性比较低。所以GTest提供了一系列近似比较的断言。

1. 默认近似度   

| Fatal assertion                 | Nonfatal assertion              | Verifies                                 |
| ------------------------------- | ------------------------------- | ---------------------------------------- |
| `ASSERT_FLOAT_EQ(val1, val2);`  | `EXPECT_FLOAT_EQ(val1, val2);`  | the two `float` values are almost equal  |
| `ASSERT_DOUBLE_EQ(val1, val2);` | `EXPECT_DOUBLE_EQ(val1, val2);` | the two `double` values are almost equal |

> 上述系列的断言的近似度为浮点数的4个[Units in the Last Place](https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/) (ULPs) 内，简单说就是把所有浮点数排序，4个ULP就是前后四位以内。

2. 自定义近似度

| Fatal assertion                       | Nonfatal assertion                    | Verifies                                                                         |
| ------------------------------------- | ------------------------------------- | -------------------------------------------------------------------------------- |
| `ASSERT_NEAR(val1, val2, abs_error);` | `EXPECT_NEAR(val1, val2, abs_error);` | the difference between `val1` and `val2` doesn't exceed the given absolute error |

```
TEST(GeneralTest, FloatAssertion)
{
  ASSERT_FLOAT_EQ(1.0000001f, 1.0f);
  // double型的浮点数密度高，1e-7在4ULP以外
  // ASSERT_DOUBLE_EQ(1.0000001, 1.0); 失败
  ASSERT_NEAR(1.009f,1.0f,0.01f);
  // 谓词判断
  EXPECT_PRED_FORMAT2(::testing::FloatLE, 1.0000001f, 1.0f);
}
```

## gmock的matcher断言
gMock带有一个匹配器库，用于验证传递给模拟对象的参数。

| Fatal assertion                | Nonfatal assertion             | Verifies              |
| ------------------------------ | ------------------------------ | --------------------- |
| `ASSERT_THAT(value, matcher);` | `EXPECT_THAT(value, matcher);` | value matches matcher |

```
TEST(GeneralTest, GMockMatcher)
{
  const std::string str("Hello 123 world!");
  EXPECT_THAT(str, ::testing::StartsWith("Hello"));
  EXPECT_THAT(str, ::testing::EndsWith("world!"));
  ASSERT_THAT(str, ::testing::HasSubstr("llo"));
  EXPECT_THAT(str, ::testing::MatchesRegex(".*[1-9]{3}.*"));
}
```

## 类断言(Type Assertion)
对类属性(type traits)进行断言，编译期执行，这个断言相较于std::type_traits而言能够产生更加友好的错误信息。
```
// 判断T1和T2是否是同一个类
::testing::StaticAssertTypeEq<T1, T2>();
```
1. 此类型断言允许我们自建谓词进行断言。一个好处是可以提供更加漂亮的错误信息。



| Fatal assertion                   | Nonfatal assertion                | Verifies                    |
| --------------------------------- | --------------------------------- | --------------------------- |
| `ASSERT_PRED1(pred1, val1)`       | `EXPECT_PRED1(pred1, val1)`       | `pred1(val1)` is true       |
| `ASSERT_PRED2(pred2, val1, val2)` | `EXPECT_PRED2(pred2, val1, val2)` | `pred2(val1, val2)` is true |
| `...`                             | `...`                             | `...`                       |


```
bool equal(int m, int n)
{
  return m==n;
}
TEST(GeneralTest, PredAssertion)
{
  const int m = 1;
  const int n = 2;
  EXPECT_PRED2(equal, m, n);
}
// Error message:
// equal(m, n) evaluates to false, where
// m evaluates to 1
// n evaluates to 2
```

2. 我们甚至可以通过一下断言自行定义错误信息输出的格式。

Fatal assertion                                  | Nonfatal assertion                               | Verifies
------------------------------------------------ | ------------------------------------------------ | --------
`ASSERT_PRED_FORMAT1(pred_format1, val1);`       | `EXPECT_PRED_FORMAT1(pred_format1, val1);`       | `pred_format1(val1)` is successful
`ASSERT_PRED_FORMAT2(pred_format2, val1, val2);` | `EXPECT_PRED_FORMAT2(pred_format2, val1, val2);` | `pred_format2(val1, val2)` is successful
`...`                                            | `...`                                            | ...



```
bool equal(int m, int n){
  return m==n;
}

// A predicate-formatter for asserting that two integers are equal
testing::AssertionResult AssertEqual(const char* m_expr, //规定格式
                                     const char* n_expr, //规定格式
                                     int m, //参数
                                     int n) { //参数
  if (equal(m, n)) return testing::AssertionSuccess();

  return testing::AssertionFailure() << m_expr << " and " << n_expr
      << " (" << m << " and " << n << ") are not equal, "
      << "as they are " << m-n << " apart.";
}
TEST(GeneralTest, PredAssertion)
{
  const int m = 2;
  const int n = 1;
  EXPECT_PRED_FORMAT2(AssertEqual, m, n);
}
```
# Reference
1. [Googletest Primer](https://github.com/google/googletest/blob/master/docs/primer.md)
2. [Advanced googletest Topics](https://github.com/google/googletest/blob/master/docs/advanced.md)