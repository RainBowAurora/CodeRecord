# 夹具测试
如果编写了两个或多个对相似数据进行测试，同一个testsuite中test往往需要类似的初始化和收尾工作，为了方便同一则可以使用googletest的夹具方法来测试。

## 构建夹具测试
构建夹具测试分为以下几个步骤:
1. 继承`::testing::Test`，类成员函数和成员变量权限设置为`protected`。
2. 在类中定义测试需要用到的对象，这样可以做到各个test 互相独立，互不影响。
3. 如有必要，可以写默认构造函数或者重载`SetUp()`函数来准备测试所需资源。gtest会在运行测试前调用SetUp()。SetUp()容易被写成Setup()，为了避免这种错误，请用`override`关键字促使编译器检测。关于什么时候用构造函数什么时候用SetUp()，请参照附录。一般推荐直接使用构造函数和析构函数。
4. 可以重载析构函数和`TearDown()`来释放由构造函数或者`SetUp()`创建的资源。
5. 定义其他成员函数，并将断言加入成员函数。这样做的一个问题是错误信息只会定位到该成员函数。
> 当使用测试夹具时，使用TEST_F()进行测试，而不是TEST()

```
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

// 使用TEST_F定义测试，第一个参数必需是测试夹具类名，第二个参数是测试名
TEST_F(QueueTest, fixtures1){
    // 直接可以使用QueueTest的成员变量
    ASSERT_EQ(q1_.front(), 10086);
    EXPECT_TRUE(q0_.size() == 1);
    q0_.pop();
    EXPECT_TRUE(q0_.empty());
}

TEST_F(QueueTest, fixtures2){
    // fixtures1 fixtures2 测试之间互不影响
    EXPECT_TRUE(q0_.size() == 1);
}
```

## 运行结果
```
[----------] 2 tests from QueueTest
[ RUN      ] QueueTest.fixtures1
SetUp
TearDown
[       OK ] QueueTest.fixtures1 (0 ms)
[ RUN      ] QueueTest.fixtures2
SetUp
TearDown
[       OK ] QueueTest.fixtures2 (0 ms)
[----------] 2 tests from QueueTest (0 ms total)
```

## Reference
1. [googletest-primer.md](https://github.com/google/googletest/blob/master/docs/primer.md)
2. [GTest系列之测试夹具（二）](https://tao-fu.gitee.io/2020/11/02/%E5%8D%95%E5%85%83%E6%B5%8B%E8%AF%95/gtest_2_test_fixture/#more)