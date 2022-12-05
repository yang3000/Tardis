#pragma once

#include <functional>
#include <utility> 
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
    Str abbr;
    Str desc;
};

typedef unsigned int  UInt;
typedef int           Int;
typedef char          Char;
typedef unsigned char UChar;
typedef char*         PChar;

enum TardisDataType
{
    TardisDataType_S8,       // signed char / char (with sensible compilers)
    TardisDataType_U8,       // unsigned char
    TardisDataType_S16,      // short
    TardisDataType_U16,      // unsigned short
    TardisDataType_S32,      // int
    TardisDataType_U32,      // unsigned int
    TardisDataType_S64,      // long long / __int64
    TardisDataType_U64,      // unsigned long long / unsigned __int64
    TardisDataType_Float,    // float
    TardisDataType_Double,   // double
    TardisDataType_Bool,     // bool
    TardisDataType_String,   // string
    TardisDataType_Pointer,  // pointer
    TardisDataType_COUNT
};

typedef void (*ParseCallBack)(const char *, Param *, unsigned);

// transform from GenSeq<N> to Seq<0,1,2,3,...,N-1>
template<int...> struct Seq {};
template<int N, int ...S> struct GenSeq : GenSeq<N - 1, N - 1, S...> {};
template<int ...S> struct GenSeq<0, S...> { typedef Seq<S...> Type; };

template<typename T> struct ValidType { static constexpr bool isValid = (!std::is_reference<T>::value) && (!std::is_pointer<T>::value); };
template<typename... Args> struct CheckParam;
template<typename T, typename... Args> struct CheckParam<T, Args...> { static constexpr bool isValid = ValidType<T>::isValid && CheckParam<Args...>::isValid; };
template<typename T> struct CheckParam <T> { static constexpr bool isValid = ValidType<T>::isValid; };

// template <typename R, typename... ArgTypes>
// auto deduce_std_function(R(*)(ArgTypes...))->std::function<R(ArgTypes...)>;

// template <typename F, typename R, typename... ArgTypes>
// auto deduce_std_function_impl(R(F::*)(ArgTypes...))->std::function<R(ArgTypes...)>;

// template <typename F, typename R, typename... ArgTypes>
// auto deduce_std_function_impl(R(F::*)(ArgTypes...) const)->std::function<R(ArgTypes...)>;

// template <typename F, typename R, typename... ArgTypes>
// auto deduce_std_function_impl(R(F::*)(ArgTypes...) &)->std::function<R(ArgTypes...)>;

// template <typename F, typename R, typename... ArgTypes>
// auto deduce_std_function_impl(R(F::*)(ArgTypes...) const&)->std::function<R(ArgTypes...)>;

// template <typename F, typename R, typename... ArgTypes>
// auto deduce_std_function_impl(R(F::*)(ArgTypes...) && )->std::function<R(ArgTypes...)>;

// template <typename F, typename R, typename... ArgTypes>
// auto deduce_std_function_impl(R(F::*)(ArgTypes...) const&&)->std::function<R(ArgTypes...)>;

// template <typename Function>
// auto deduce_std_function(Function)
// -> decltype(deduce_std_function_impl(&Function::operator()));

// template <typename Function>
// using deduce_std_function_t = decltype(deduce_std_function(std::declval<Function>()));

// template <typename F>
// auto to_std_function(F&& fn) -> deduce_std_function_t<F> {
// 	return deduce_std_function_t<F>(std::forward<F>(fn));
// }