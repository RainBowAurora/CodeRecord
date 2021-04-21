#include <iostream>
#include <fstream>
#include <glob.h>
#include <vector>
#include <dirent.h> //for DIR mkdir()
#include <string.h> //for strcmp
#include <errno.h>
#include <unistd.h> //for unlink mkdir rmdir
#include <sstream> //for std::stringstream

#include <sys/mman.h>
#include <sys/stat.h>

#include "cyber_file.h"

namespace common{

/**
 * @brief 拼接前缀和后缀获取完整路径
 * 
 * @param prefix 前缀
 * @param relative_path 后缀
 * @return std::string 完整路径
 */
std::string GetAbsolutePath(const std::string &prefix,
                            const std::string &relative_path)
{
    if( relative_path.empty() ) return prefix;
    //无前缀或者相对路径已经是绝对路径
    if( prefix.empty() || relative_path.front() == '/' ){
        return relative_path;
    }
    if( prefix.back() == '/' ){ 
        return prefix + relative_path; //前缀+后缀
    }
    return prefix + "/" + relative_path; //前缀+'/'+后缀
}

/**
 * @brief 获取内容对象
 * 
 * @param file_name 文件名
 * @param content 文件内容
 * @return true 获取成功
 * @return false 获取失败
 */
bool GetContent(const std::string &file_name, std::string *content)
{
    std::ifstream fin(file_name);
    if(!fin) { return false; }

    std::stringstream str_stream;
    str_stream << fin.rdbuf();

    *content = str_stream.str();
    return true;
}

/**
 * @brief 检查路径是否存在
 * 
 * @param path 文件路径
 * @return true 获取成功
 * @return false 获取失败
 */
bool PathExists(const std::string &path) {
    struct stat info;
    //[C语言stat()函数获取文件状态](https://www.cnblogs.com/jikexianfeng/p/5742887.html)
    return stat(path.c_str(), &info) == 0;
}

/**
 * @brief 检查目录是否存在
 * 
 * @param directory_path 文件路径
 * @return true 获取成功
 * @return false 获取失败
 */
bool DirectoryExists(const std::string &directory_path) {
  struct stat info;
  return stat(directory_path.c_str(), &info) == 0 && (info.st_mode & S_IFDIR);
}

/**
 * @brief 获取当前目录下所有文件的名字
 * 
 * @param pattern 文件路径
 * @return std::vector<std::string> 目录下的子文件名字
 */
std::vector<std::string> Glob(const std::string &pattern) {
    glob_t globs = {};
    std::vector<std::string> results;
    if (glob(pattern.c_str(), GLOB_TILDE, nullptr, &globs) == 0) {
        for (size_t i = 0; i < globs.gl_pathc; ++i) {
            results.emplace_back(globs.gl_pathv[i]);
        }
    }
    globfree(&globs);
    return results;
}

/**
 * @brief 拷贝文件
 * 
 * @param from source path
 * @param to target path
 * @return true 拷贝成功
 * @return false 拷贝失败
 */
bool CopyFile(const std::string &from, const std::string &to) {
    std::ifstream src(from, std::ios::binary);
     if (!src) {
        std::cout << "ERROR: Source path could not be normally opened: " << from;
        std::string command = "cp -r " + from + " " + to;
        std::cout << command;
        const int ret = std::system(command.c_str());
        if (ret == 0) {
            std::cout << "Copy success, command returns " << ret;
            return true;
        }else{
            std::cout << "Copy error, command returns " << ret;
            return false;
        }
     }
    std::ofstream dst(to, std::ios::binary);
    if (!dst) { //目标路径不可写
        std::cout << "Target path is not writable: " << to;
        return false;
    }
    dst << src.rdbuf();
        return true;
}

/**
 * @brief 目录拷贝
 * 
 * @param from source dir
 * @param to target dir
 * @return true 拷贝成功
 * @return false 拷贝失败
 */
bool CopyDir(const std::string &from, const std::string &to) {
    DIR *directory = opendir(from.c_str());
    if (directory == nullptr) {
        std::cout << "Cannot open directory " << from;
        return false;
    }
    bool ret = true;

    if (EnsureDirectory(to)) {
        struct dirent *entry;
        while ((entry = readdir(directory)) != nullptr) {
            // skip directory_path/. and directory_path/..
            if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..")) {
                continue;
            }
            const std::string sub_path_from = from + "/" + entry->d_name;
            const std::string sub_path_to = to + "/" + entry->d_name;
            if (entry->d_type == DT_DIR) {
                ret &= CopyDir(sub_path_from, sub_path_to);
            }else{
                ret &= CopyFile(sub_path_from, sub_path_to);
            }
        }
    }else{
        std::cout << "Cannot create target directory " << to;
        ret = false;
    }
    closedir(directory);
    return true;
}

/**
 * @brief 拷贝文件and目录拷贝
 * 
 * @param from source dir
 * @param to target dir
 * @return true 拷贝成功
 * @return false 拷贝失败
 */
bool Copy(const std::string &from, const std::string &to) {
  return DirectoryExists(from) ? CopyDir(from, to) : CopyFile(from, to);
}

/**
 * @brief 创建目录
 * 
 * @param directory_path 需要创建的路径
 * @return true  创建成功
 * @return false 创建失败
 */
bool EnsureDirectory(const std::string &directory_path) {
    std::string path = directory_path;
    for (size_t i = 1; i < directory_path.size(); ++i) {
        if (directory_path[i] == '/') {
            // Whenever a '/' is encountered, create a temporary view from
            // the start of the path to the character right before this.
            path[i] = 0;
            if (mkdir(path.c_str(), S_IRWXU) != 0) {
                if (errno != EEXIST)  return false;
            }
            // Revert the temporary view back to the original.
            path[i] = '/';
        }
    }
    // Make the final (full) directory.
    if (mkdir(path.c_str(), S_IRWXU) != 0) {
        if (errno != EEXIST)  return false;
    }

    return true;
}

/**
 * @brief 删除指定路径下的所有文件
 * 
 * @param directory_path 路径
 * @return true 删除成功
 * @return false 删除失败
 */
bool RemoveAllFiles(const std::string &directory_path) {
    DIR *directory = opendir(directory_path.c_str());
    if (directory == nullptr) {
        std::cout << "Cannot open directory " << directory_path;
        return false;
    }

    struct dirent *file;
    while ((file = readdir(directory)) != nullptr) {
        // skip directory_path/. and directory_path/..
        if (!strcmp(file->d_name, ".") || !strcmp(file->d_name, "..")) {
            continue;
        }
        // build the path for each file in the folder
        std::string file_path = directory_path + "/" + file->d_name;
        if (unlink(file_path.c_str()) < 0) { //remove file
            std::cout << "ERROR: Fail to remove file " << file_path << ": " << strerror(errno);
            closedir(directory);
            return false;
        }
    }
    closedir(directory);
    
    return true;
}

/**
 * @brief Get the File Name object 获取文件名字
 * 
 * @param path 路径+文件名字
 * @param remove_extension 是否删除扩展名
 * @return std::string 文件名字
 */
std::string GetFileName(const std::string &path, const bool remove_extension) {
  std::string::size_type start = path.rfind('/');
  if (start == std::string::npos) {
    start = 0;
  } else {
    // Move to the next char after '/'. 跳过最后一个'/'
    ++start;
  }

  std::string::size_type end = std::string::npos;
  if (remove_extension) {
    end = path.rfind('.');
    // The last '.' is found before last '/', ignore.
    if (end != std::string::npos && end < start) {
      end = std::string::npos;
    }
  }
  //截取从最后一个'/'开始到'.'为止的字符串，即文件名
  const auto len = (end != std::string::npos) ? end - start : end;
  //[substr库函数](https://en.cppreference.com/w/cpp/string/basic_string/substr)
  return path.substr(start, len);
}


/**
 * @brief Get the Current Path object 获取当前所在目录
 * 
 * @return std::string 目录名字
 */
std::string GetCurrentPath() {
  char tmp[PATH_MAX];
  //[C中getcwd()用法]https://blog.csdn.net/u013889888/article/details/45099113
  return getcwd(tmp, sizeof(tmp)) ? std::string(tmp) : std::string("");
}

/**
 * @brief 列出当前路径下所有子目录
 * 
 * @param directory_path 
 * @param d_type 
 * @return std::vector<std::string> 
 */
std::vector<std::string> ListSubPaths(const std::string &directory_path,
                                      const unsigned char d_type) {
  std::vector<std::string> result;
  DIR *directory = opendir(directory_path.c_str());
  if (directory == nullptr) {
    std::cout << "Cannot open directory " << directory_path;
    return result;
  }

  struct dirent *entry;
  while ((entry = readdir(directory)) != nullptr) {
    // Skip "." and "..".
    if (entry->d_type == d_type && strcmp(entry->d_name, ".") != 0 &&
        strcmp(entry->d_name, "..") != 0) {
      result.emplace_back(entry->d_name);
    }
  }
  closedir(directory);
  return result;
}

/**
 * @brief 创建文件
 * 
 * @param dir 文件名和路径
 * @return true 创建成功
 * @return false 创建失败
 */
bool CreateDir(const std::string &dir) {
  int ret = mkdir(dir.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
  if (ret != 0) {
    std::cout << "failed to create dir. [dir: " << dir
          << "] [err: " << strerror(errno) << "]";
    return false;
  }
  return true;
}

/**
 * @brief Get the Type object
 * 
 * @param filename path
 * @param type file type
 * @return true 
 * @return false 
 */
bool GetType(const std::string &filename, FileType *type) {
  struct stat stat_buf;
  if (lstat(filename.c_str(), &stat_buf) != 0) {
    return false;
  }
  if (S_ISDIR(stat_buf.st_mode) != 0) {
    *type = TYPE_DIR;
  } else if (S_ISREG(stat_buf.st_mode) != 0) {
    *type = TYPE_FILE;
  } else {
    std::cout << "[ERRO] failed to get type: " << filename;
    return false;
  }
  return true;
}


/**
 * @brief Delete File
 * 
 * @param filename 
 * @return true 
 * @return false 
 */
bool DeleteFile(const std::string &filename) {
  if (!PathExists(filename)) {
    return true;
  }
  FileType type;
  if (!GetType(filename, &type)) {
    return false;
  }
  if (type == TYPE_FILE) {
    if (remove(filename.c_str()) != 0) {
      std::cout << "[ERROR] failed to remove file: " << filename;
      return false;
    }
    return true;
  }
  DIR *dir = opendir(filename.c_str());
  if (dir == nullptr) {
    std::cout << "failed to opendir: " << filename;
    return false;
  }
  dirent *dir_info = nullptr;
  while ((dir_info = readdir(dir)) != nullptr) {
    if (strcmp(dir_info->d_name, ".") == 0 ||
        strcmp(dir_info->d_name, "..") == 0) {
      continue;
    }
    std::string temp_file = filename + "/" + std::string(dir_info->d_name);
    FileType temp_type;
    if (!GetType(temp_file, &temp_type)) {
      std::cout << "[ERROR] failed to get file type: " << temp_file;
      closedir(dir);
      return false;
    }
    if (type == TYPE_DIR) {
      DeleteFile(temp_file);
    }
    remove(temp_file.c_str());
  }
  closedir(dir);
  remove(filename.c_str());
  return true;
}

} //end namespace common