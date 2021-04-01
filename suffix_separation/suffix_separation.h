#ifndef __SUFFIX_SEPARATION_H__
#define __SUFFIX_SEPARATION_H__

#include <iostream>
#include <regex>
#include <string>
#include <tuple>

#include <sys/stat.h> // for mkdir()
#include <sys/types.h> // for opendir()
#include <dirent.h>


#define FILE_NAME strrchr(__FILE__,'/')?strrchr(__FILE__,'/')+1:__FILE__

//获取文件名:std::tople<0>, 后缀名: std::tople<1>
std::tuple<std::string, std::string> PathFindExtension(const std::string& path)
{
    std::regex re(R"((.+?)(\.[^.]+)?)");
    std::smatch results;
    std::regex_match(path, results, re);
    return {results[1], results[2]};
}

#endif /*__SUFFIX_SEPARATION_H__*/

