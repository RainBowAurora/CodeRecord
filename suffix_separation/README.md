# 文件名和后缀名分离
我们日常写代码经常会遇到根据后缀名判断文件类型，或将后缀名去掉取文件名的操作，如果自己进行字符串分割会很麻烦，这里介绍一个方便快捷的方法。

## 使用方法
1. 将头文件包含进工程
```
#include "suffix_separation.h"
```

2. 将要进行分离的名字(例如AAA.xxx)放入函数中
```
auto result =  PathFindExtension(std::string(AAA.xxx))
```

3. 从结果中获取文件名和后缀名
```
std::string file_name = std::get<0>(); //文件名 AAA
std::string suffix_name = std::get<1>(); //后缀名 .XXX
```
