#ifndef __DEFINE_TYPE_TRAIT_H__
#define __DEFINE_TYPE_TRAIT_H__


#define DEFINE_TYPE_TRAIT(name, func)                   \
template <typename T>                                   \
struct name{                                            \
template <typename Class>                               \
static constexpr bool Test(decltype(&Class::func)*){    \
    return true;                                        \
}                                                       \
template <typename Class>                               \
static constexpr bool Test(...){                        \
    return false;                                       \
}                                                       \
static constexpr bool value = Test<T>(nullptr);         \
};                                                      \
                                                        \
// template <typename T>                                \
// constexpr bool name<T>::value;




#endif /*__DEFINE_TYPE_TRAIT_H__*/