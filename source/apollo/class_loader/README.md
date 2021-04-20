# POCO动态加载
现代操作系统几乎都提供了共享库动态加载的功能。linux提供了dlopen函数来加载共享库。十分粗略地讲，共享库加载就是加载共享库文件，根据函数名符号找到函数的地址，然后调用函数。[poco](https://github.com/pocoproject/poco.git)库是一个跨平台的通用C++库，封装了不同平台上的共享库加载功能。

## 使用g++生成和链接动态库方法
1. g++编译生成so文件
```
g++ hello.cpp -fPIC -shared -o libhello.so
```
> 说明
> * **-fPIC**：表示编译为位置独立的代码，不用此选项的话编译后的代码是位置相关的>所以动态载入时是通过代码拷贝的方式来满足不同进程的需要，而不能达到真正代码段共享
的目的。  
> * **-L.**：表示要连接的库在当前目录中  
> * **-lxxx**：编译器查找动态连接库时有隐含的命名规则，即在给出的名字前面加上lib，后面加上.so来确定库的名称libxxx.so 

2. 生成可执行文件
```
g++ main.cpp -L. -lhello -o main
```
> 修改环境变量 `export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.` 否则无法运行

## Poco动态加载类简单案例
* print_hello.h
```
#ifndef __POCO_PRINT_H__
#define __POCO_PRINT_H__
#include <iostream>
// 使用C的函数符号，C++的函数符号不直观。
extern "C" void  print_hello();

#endif /*__POCO_PRINT_H__*/
```

* print_hello.cpp
```
void print_hello()
{
    std::cout << "Hello world" << std::endl;
}
```

* main.cpp
```
#include <Poco/SharedLibrary.h>

using Poco::SharedLibrary;
typedef void (*HelloFunc)(); // function pointer type
int main(int argc, char **argv)
{
    std::string path("/home/tt/workspace/my_test/build/libhello.so"); //动态库.so路径
    SharedLibrary library(path);          // will also load the library
    HelloFunc func = (HelloFunc)library.getSymbol("print_hello");
    func(); //使用函数
    library.unload();
    return 0;
}
```

* CMakeLists.txt
```
cmake_minimum_required(VERSION 3.4)

project(test_poco)

add_library(hello SHARED hello.cpp) //生成动态库 libhello.so

find_package(Poco REQUIRED COMPONENTS Foundation) //寻找POCO

add_executable(${PROJECT_NAME}_node main.cpp)
target_link_libraries(${PROJECT_NAME}_node Poco::Foundation)
```
## apollo/Cyber中的class_loader的使用
* 子类实现基类的各种接口，然后在子类cpp文件中使用宏CLASS_LOADER_REGISTER_CLASS(DerivedClass, BaseClass);来将子类注册入一个全局的静态变量中。
```
//------Base
class Base {
 public:
  virtual void DoSomething() = 0;
  virtual ~Base() {}
};

//------Star
class Star : public Base {
 public:
  virtual void DoSomething() { std::cout << "I am Star" << std::endl; }
};

//生成一个静态的Star对象 
CLASS_LOADER_REGISTER_CLASS(Star, Base);
```

* 接着我们可以使用类名字符串直接创建子类的实例。cyber/class_loader/class_loader_test.cc提供了一个样例。
```
const char LIBRARY_1[] =
    "/apollo/bazel-bin/cyber/class_loader/test/libplugin1.so";

ClassLoaderManager loader_mgr;
loader_mgr.CreateClassObj<Base>("Star")->DoSomething();
```

## Reference
1. [Cyber源代码之动态加载类 class_loader （一）](https://tao-fu.gitee.io/2020/12/05/%E6%9C%BA%E5%99%A8%E4%BA%BA%E6%9E%B6%E6%9E%84/cyber_class_loader_01/#more)
2. [apollo/Cpber/class_loader](https://github.com/ApolloAuto/apollo/tree/master/cyber/class_loader)