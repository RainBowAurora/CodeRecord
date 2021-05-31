# POCO动态加载
classloader直译过来是类加载器，类加载器主要用来动态加载库文件，动态加载是一种机制，计算机程序可以通过这种机制在运行时将库（或者其它二进制文件）加载到内存中，检索库中包含的函数和变量的地址，执行这些函数或访问这些变量。[poco](https://github.com/pocoproject/poco.git)库是一个跨平台的通用C++库，封装了不同平台上的共享库加载功能。

## 动态加载的优缺点
* 优点: 
    1. 运行时更加灵活，可以动态的加载启动功能。
    2. 可以使用第三方的工具进行扩展
* 缺点: 
    1. 启动时间会慢20%
    2. 执行效率慢了5%，由于动态地址解析PIC

## 程序运行机制
1. 静态链接 (static linking): 静态链接会把程序拷贝一份到可执行程序，带来的好处是不依赖任何外部程序就可以独立运行，坏处是浪费磁盘和内存空间。
2. 动态链接 (dynamic linking): 动态链接和静态链接相反，动态链接是在编译时候指定链接到哪个库，在运行时查找对应的库并且加载到内存，而且不同的应用程序在内存中可以共享一份动态库，从而节省系统内存
3. 动态加载 (dynamic loading): 指的是当一个进程启动后，将一个可执行的文件（原文是executable，我理解为磁盘上的文件 或者驻留在内存中的例程）或库映射到（或者不常发生的复制）到进程内存空间。
> [动态加载和东台链接之间的区别](https://blog.csdn.net/giantpoplar/article/details/46485649)

### 使用g++生成和链接动态库方法
4. g++编译生成so文件
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

3. 我们可以通过`ldd ./main`来查看运行程序依赖于哪些动态库
```
linux-vdso.so.1 (0x00007ffc4d19a000)
libhello.so => /lib/libhello.so (0x00007f2452dbb000)
libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f24529ca000)
/lib64/ld-linux-x86-64.so.2 (0x00007f24531bf000)
...
```

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