# yaml-cpp快速使用
YAML 是 "YAML Ain't a Markup Language"（YAML 不是一种标记语言）的递归缩写。在开发的这种语言时，YAML 的意思其实是："Yet Another Markup Language"（仍是一种标记语言）。YAML 的配置文件后缀为 .yml。YAML 的语法和其他高级语言类似，并且可以简单表达清单、散列表，标量等数据形态。它使用空白符号缩进和大量依赖外观的特色，特别适合用来表达或编辑数据结构、各种配置文件、倾印调试内容、文件大纲（例如：许多电子邮件标题格式和YAML非常接近）。

## yaml-cpp安装
1. 获取源码
```
git clone https://github.com/jbeder/yaml-cpp.git
git checkout yaml-cpp-0.6.3 #例程中使用的是0.6.3的版本
```
2. 编译
```
cd yaml-cpp
mkdir build && cd build
cmake DYAML_BUILD_SHARED_LIBS=ON ..
make
```
> yaml默认不会编译动态库.so，需要在编译时明显指定`DYAML_BUILD_SHARED_LIBS=ON`

3. 安装
```
sudo make install #这里需要用到临时管理员权限
```

## YAML操作
### 基本构建
```
YAML::Node node;  // starts out as null
node["key"] = "value";  // it now is a map node
node["seq"].push_back("first element");  // node["seq"] automatically becomes a sequence
node["seq"].push_back("second element");

node["mirror"] = node["seq"][0];  // this creates an alias
node["seq"][0] = "1st element";  // this also changes node["mirror"]
node["mirror"] = "element #1";  // and this changes node["seq"][0] - they're really the "same" node

node["self"] = node;  // you can even create self-aliases
node[node["mirror"]] = node["seq"];  // and strange loops :)
```
上述节点格式:
```
&1
key: value
&2 seq: [&3 "element #1", second element]
mirror: *3
self: *1
*3 : *2
```


### 文件读取和写入
```
YAML::Node config = YAML::LoadFile("config.yaml"); //文件读取

if (config["lastLogin"]) {
  std::cout << "Last logged in: " << config["lastLogin"].as<DateTime>() << "\n";
}

const std::string username = config["username"].as<std::string>();
const std::string password = config["password"].as<std::string>();
login(username, password);
config["lastLogin"] = getCurrentDateTime();

std::ofstream fout("config.yaml"); //文件写入
fout << config;
fout.close();
```


### 基本类型解析
1. 数组
```
YAML::Node primes = YAML::Load("[2, 3, 5, 7, 11]");
assert(node.Type() == YAML::NodeType::Sequence);
for (std::size_t i=0;i<primes.size();i++) {
  std::cout << primes[i].as<int>() << "\n";
}
// or:
for (YAML::const_iterator it=primes.begin();it!=primes.end();++it) {
  std::cout << it->as<int>() << "\n";
}

primes.push_back(13);
assert(primes.size() == 6);
```

2. 字符串
```
YAML::Node lineup = YAML::Load("{1B: Prince Fielder, 2B: Rickie Weeks, LF: Ryan Braun}");
for(YAML::const_iterator it=lineup.begin();it!=lineup.end();++it) {
  std::cout << "Playing at " << it->first.as<std::string>() << " is " << it->second.as<std::string>() << "\n";
}

lineup["RF"] = "Corey Hart";
lineup["C"] = "Jonathan Lucroy";
assert(lineup.size() == 5);
```

### 类型判断
```
YAML::Node node;

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
```

### 自建类型
1. 给自定义类型添加编码和解码
```
struct Vec3 { double x, y, z; /* etc - make sure you have overloaded operator== */ };

namespace YAML {
template<>
struct convert<Vec3> {
  static Node encode(const Vec3& rhs) {
    Node node;
    node.push_back(rhs.x);
    node.push_back(rhs.y);
    node.push_back(rhs.z);
    return node;
  }

  static bool decode(const Node& node, Vec3& rhs) {
    if(!node.IsSequence() || node.size() != 3) {
      return false;
    }

    rhs.x = node[0].as<double>();
    rhs.y = node[1].as<double>();
    rhs.z = node[2].as<double>();
    return true;
  }
};
}

```

2. 使用自定义类型
```
YAML::Node node = YAML::Load("start: [1, 3, 0]");
Vec3 v = node["start"].as<Vec3>();
node["end"] = Vec3(2, -1, 0);
```

## YAML格式
1. array
```
YAML::Node node;
std::vector<int> vec = {1,2,3,4};
node["array"] = vec;
node["array"].SetStyle(YAML::EmitterStyle::Flow);
/*
array: [1, 2, 3, 4]
*/
```
2. vec
```
YAML::Node node;
std::vector<int> vec = {1,2,3,4};
node["vec"] = vec;
node["vec"].SetStyle(YAML::EmitterStyle::Block);

/*
array:
  - 1
  - 2
  - 3
  - 4
  - 5
*/
```

## Reference
* [How-To-Emit-YAML.md](https://github.com/jbeder/yaml-cpp/blob/master/docs/How-To-Emit-YAML.md)
* [Tutorial.md](https://github.com/jbeder/yaml-cpp/blob/master/docs/Tutorial.md)