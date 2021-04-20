#include <iostream>
#include "factory.h"


Base* create_object(const std::string& derived_class_name)
{
    const auto creator_list = get_creator_list();
    return creator_list.at(derived_class_name)();
}

CreatorList& get_creator_list(){
    static CreatorList creator_list; 
    return creator_list;
}

void add_creator_list(const std::string& derived_class_name, object_creator_func func){
    auto& creator_lists = get_creator_list();
    creator_lists.emplace(derived_class_name, func);
}