#ifndef __CLASS_LOADER_FACTORY_H__
#define __CLASS_LOADER_FACTORY_H__

#include <iostream>
#include <string>
#include <map>

#include "base.h"

// 创造函数的类型
using object_creator_func = Base* (*)();

// 类名到创造函数的map
using CreatorList = std::map<std::string, object_creator_func>;

// 利用类名来创建其对象
Base* create_object(const std::string& derived_class_name);

// 获得一个静态变量
CreatorList& get_creator_list();

// 将类的创造函数加入一个静态变量
void add_creator_list(const std::string& derived_class_name, object_creator_func func);

#endif /*__CLASS_LOADER_FACTORY_H__*/
