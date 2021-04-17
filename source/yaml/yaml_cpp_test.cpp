#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include <yaml-cpp/yaml.h>

using namespace std;

int main(int argc,char** argv)
{
    YAML::Node node;
    assert(node.IsNull());  //初始化的节点是Null类型
    node["key"] = "value";  //当你给它赋值键值对，它转变为Map类型
    if(node["mascot"]){
         std::cout << node["mascot"].as<std::string>() << "";
    }//单纯的查询操作不会增加一个key

    node["number"] = 255;
    assert(node.IsMap());   //node是一个Map
    node["seq"].push_back("first element");
    node["seq"].push_back("second element");//node的seq下是Sequence类型，有两个参数

    std::cout << node << std::endl;
    return 0;
}