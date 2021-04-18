#include <iostream>
#include <string>
#include <assert.h>
#include <yaml-cpp/yaml.h>
#include <fstream>
#include <libgen.h> //for

using namespace std;

const std::string FILE_NAME = "test.yaml";

void TypeTraits(const YAML::Node& node)
{
    switch(node.Type()){
    case YAML::NodeType::Null: 
        std::cout << "YAML::NodeType::Null\n"; break;
    case YAML::NodeType::Scalar:
        std::cout << "YAML::NodeType::Scalar\n"; break;
    case YAML::NodeType::Sequence: 
        std::cout << "YAML::NodeType::Sequence\n"; break;
    case YAML::NodeType::Map: 
        std::cout << "YAML::NodeType::Map\n"; break;
    case YAML::NodeType::Undefined:
        std::cout << "YAML::NodeType::Undefined\n"; break;
    }
}

void WriteYamlFile(const std::string& file_name)
{
    YAML::Node node;
    assert(node.IsNull());

    node["key"] = "value";  //当你给它赋值键值对，它转变为Map类型
    node["number"] = 255;

    std::vector<int> vec = {1, 2, 3, 4, 5};
    node["array"] = vec;
    node["array"].SetStyle(YAML::EmitterStyle::Flow);
    //array: [1, 2, 3, 4, 5]

    YAML::Node node_2;  
    node_2.push_back("first item");//如果你不给node_2键值对，它是一个sequence类型
    node_2.push_back("second_item");
    node_2.push_back("third_item");
    node_2.push_back(vec);

    node["node2"] = node_2;

    //写文件
    std::ofstream file(file_name);
    file << node << std::endl;
    TypeTraits(node);
    file.close();
}

void ReadYamlFile(const std::string& file_name)
{
    YAML::Node node = YAML::LoadFile(file_name);

    for(auto iter = node.begin(); iter != node.end(); iter++){
        std::cout << (*iter).first << std::endl;
    }

    std::cout << node["node2"][0].as<std::string>() << std::endl;
    std::cout << node["number"].as<int>() << std::endl;
}


int main(int argc,char** argv)
{
    WriteYamlFile(FILE_NAME);
    ReadYamlFile(FILE_NAME);

    return 0;
}