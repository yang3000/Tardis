#pragma once

#include <type_traits>

#   ifndef TARDIS_EXPORTS
#       define TARDIS_EXPORT __declspec(dllexport)
#   else
#       define TARDIS_EXPORT __declspec(dllimport)
#   endif

struct Str
{
    const char* buf;
    unsigned len;
};

struct Param
{
    Str name;
    Str type;
    Str desc;
};

typedef unsigned int  UInt;
typedef int           Int;
typedef char          Char;
typedef unsigned char UChar;
typedef char*         PChar;

typedef void (*ParseCallBack)(const char *, Param *, unsigned);

// transform from GenSeq<N> to Seq<0,1,2,3,...,N-1>
template<int...> struct Seq {};
template<int N, int ...S> struct GenSeq : GenSeq<N - 1, N - 1, S...> {};
template<int ...S> struct GenSeq<0, S...> { typedef Seq<S...> Type; };

template<typename T> struct ValidType { static constexpr bool isValid = (!std::is_reference<T>::value) && (!std::is_pointer<T>::value); };
template<typename... Args> struct CheckParam;
template<typename T, typename... Args> struct CheckParam<T, Args...> { static constexpr bool isValid = ValidType<T>::isValid && CheckParam<Args...>::isValid; };
template<typename T> struct CheckParam <T> { static constexpr bool isValid = ValidType<T>::isValid; };


// template <typename R, typename... Args>
// struct function_traits_helper
// {
//     static constexpr auto param_count = sizeof...(Args);
//     using return_type = R;
//     template <std::size_t N>
//     using param_type = std::tuple_element_t<N, std::tuple<Args...>>;
// };

// template <typename T>
// struct function_traits;

// template <typename ClassType, typename R, typename... Args>
// struct function_traits<R(ClassType::*)(Args...) const> : public function_traits_helper<R, Args...>
// {
//     using class_type = ClassType;
// };

// template <typename T>
// struct function_traits : public function_traits<decltype(&T::operator())> {};