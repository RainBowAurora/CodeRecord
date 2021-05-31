#ifndef __DECLARE_SINGLETON_H__
#define __DECLARE_SINGLETON_H__

#include <iostream>
#include <mutex>
#include "define_type_trait.h"
/**
 * @brief 使用c++ 11 和成员函数内部的静态变量特性构建线程安全单例
 * 
 */
DEFINE_TYPE_TRAIT(HasShutdown, Shutdown)

template <typename T>
typename std::enable_if<HasShutdown<T>::value>::type CallShutdown(T *instance) {
  instance->Shutdown();
  std::cout << "instance->Shutdown();\n";
}

template <typename T>
typename std::enable_if<!HasShutdown<T>::value>::type CallShutdown(T *instance) {
  (void)instance;
    std::cout << "  (void)instance;\n";
}

// There must be many copy-paste versions of these macros which are same
// things, undefine them to avoid conflict.
#undef UNUSED

#define UNUSED(param) (void)param

#undef DISALLOW_COPY_AND_ASSIGN
#define DISALLOW_COPY_AND_ASSIGN(classname) \
  classname(const classname &) = delete;    \
  classname &operator=(const classname &) = delete;

#define DECLARE_SINGLETON(classname)                                      \
 public:                                                                  \
  static classname *Instance(bool create_if_needed = true) {              \
    static classname *instance = nullptr;                                 \
    if (!instance && create_if_needed) {                                  \
      static std::once_flag flag;                                         \
      std::call_once(flag,                                                \
                     [&] { instance = new (std::nothrow) classname(); }); \
    }                                                                     \
    return instance;                                                      \
  }                                                                       \
                                                                          \
  static void CleanUp() {                                                 \
    auto instance = Instance(false);                                      \
    if (instance != nullptr) {                                            \
      CallShutdown(instance);                                             \
    }                                                                     \
  }                                                                       \
                                                                          \
 private:                                                                 \
  classname() = default;                                                            \
  DISALLOW_COPY_AND_ASSIGN(classname)

#endif /*__DECLARE_SINGLETON_H__*/