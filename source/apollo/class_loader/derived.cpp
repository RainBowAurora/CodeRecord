#include "base.h"
#include "derived.h"
#include "factory.h"


void Derived::print_name()
{
    std::cout << "Derived::print_name\n";
}

int Derived::add(int a, int b)
{
    return a+b;
}

// 帮助类，利用动态库加载时会初始化静态变量的特性来将基类的creator
// 注册入一个全局函数表。
struct ClassRegistry {
    ClassRegistry() {
        get_creator_list().emplace("Derived", []() -> Base* {
            return new Derived; 
        });
    }
};

// 帮族类的静态变量。
static  ClassRegistry class_registry_derived{};