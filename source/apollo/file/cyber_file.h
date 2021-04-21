#ifndef __COMMON_FILE_H__
#define __COMMON_FILE_H__

#include <iostream>
#include <dirent.h> //for DT_DIR
// #include <yaml-cpp/yaml.h>

namespace common{

// file type: file or directory
enum FileType { TYPE_FILE, TYPE_DIR };

/**
 * @brief Get file content as string.
 * @param file_name The name of the file to read content.
 * @param content The file content.
 * @return If the action is successful.
 */
bool GetContent(const std::string &file_name, std::string *content);

/**
 * @brief Get absolute path by concatenating prefix and relative_path.
 * @return The absolute path.
 */
std::string GetAbsolutePath(const std::string &prefix,
                            const std::string &relative_path);

/**
 * @brief Check if the path exists.
 * @param path a file name, such as /a/b/c.txt
 * @return If the path exists.
 */
bool PathExists(const std::string &path);


/**
 * @brief Check if the directory specified by directory_path exists
 *        and is indeed a directory.
 * @param directory_path Directory path.
 * @return If the directory specified by directory_path exists
 *         and is indeed a directory.
 */
bool DirectoryExists(const std::string &directory_path);


/**
 * @brief Expand path pattern to matched paths.
 * @param pattern Path pattern, which may contain wildcards [?*].
 * @return Matched path list.
 */
std::vector<std::string> Glob(const std::string &pattern);


/**
 * @brief Copy a file.
 * @param from The file path to copy from.
 * @param to The file path to copy to.
 * @return If the action is successful.
 */
bool CopyFile(const std::string &from, const std::string &to);

/**
 * @brief Copy a directory.
 * @param from The path to copy from.
 * @param to The path to copy to.
 * @return If the action is successful.
 */
bool CopyDir(const std::string &from, const std::string &to);

/**
 * @brief Copy a file or directory.
 * @param from The path to copy from.
 * @param to The path to copy to.
 * @return If the action is successful.
 */
bool Copy(const std::string &from, const std::string &to);

/**
 * @brief Check if a specified directory specified by directory_path exists.
 *        If not, recursively create the directory (and its parents).
 * @param directory_path Directory path.
 * @return If the directory does exist or its creation is successful.
 */
bool EnsureDirectory(const std::string &directory_path);

/**
 * @brief Remove all the files under a specified directory. Note that
 *        sub-directories are NOT affected.
 * @param directory_path Directory path.
 * @return If the action is successful.
 */
bool RemoveAllFiles(const std::string &directory_path);

/**
 * @brief List sub-paths.
 * @param directory_path Directory path.
 * @param d_type Sub-path type, DT_DIR for directory, or DT_REG for file.
 * @return A vector of sub-paths, without the directory_path prefix.
 */
std::vector<std::string> ListSubPaths(const std::string &directory_path,
                                      const unsigned char d_type = DT_DIR);

std::string GetFileName(const std::string &path,
                        const bool remove_extension = false);

std::string GetCurrentPath();

bool DeleteFile(const std::string &filename);

bool GetType(const std::string &filename, FileType *type);

bool CreateDir(const std::string &dir);

}// end namespace common

#endif /*__COMMON_FILE_H__*/

