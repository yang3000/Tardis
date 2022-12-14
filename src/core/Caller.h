#pragma once

#include <string>
#include <assert.h>
#include <type_traits>

#include "Base.h"
#include "ICaller.h"
#include "ValueHelper.h"

namespace TARDIS::CORE
{
    // 实现从任意成员函数到bool(*)(Str* params)的转化
    template <typename T, typename R, typename... Args>
    class Caller : public ICaller
    {
    public:
        using Fn = R(T::*)(Args...);

        Caller(Fn fn, T *obj) : m_fn(fn), m_obj(obj) {}

        template <int... S> 
        R call(Seq<S...>, Str *params) 
        { 
            assert(m_obj); 
            assert(m_fn); 
            return (m_obj->*m_fn)(ValueHelper<Args>::from(std::string(params[S].buf, params[S].len))...); 
        }

        bool operator()(Str *params) 
        { 
            R res = call(m_seq, params); 
            return !!res; 
        }

        template <int... S> 
        R call(Seq<S...>, MemoryBuffer *params) 
        { 
            assert(m_obj); 
            assert(m_fn); 
            return (m_obj->*m_fn)(ValueHelper<Args>::from(params[S])...); 
        }

        bool operator()(MemoryBuffer *params) 
        { 
            R res = call(m_seq, params); 
            return !!res; 
        }

    private:
        Fn m_fn;
        T *m_obj;
        typename GenSeq<sizeof...(Args)>::Type m_seq;
    };

    // 实现从任意成员函数到bool(*)(Str* params)的转化
    template <typename T, typename... Args>
    class Caller<T, void, Args...> : public ICaller
    {
    public:
        using Fn = void(T::*)(Args...);

        Caller(Fn fn, T *obj) : m_fn(fn), m_obj(obj) {}

        template <int... S> 
        void call(Seq<S...>, Str *params) 
        { 
            assert(m_obj); 
            assert(m_fn); 
            (m_obj->*m_fn)(ValueHelper<Args>::from(std::string(params[S].buf, params[S].len))...); 
        }

        bool operator()(Str *params) 
        { 
            call(m_seq, params); 
            return true; 
        }

        template <int... S> 
        void call(Seq<S...>, MemoryBuffer *params) 
        { 
            assert(m_obj); 
            assert(m_fn); 
            (m_obj->*m_fn)(ValueHelper<Args>::from(params[S])...); 
        }

        bool operator()(MemoryBuffer *params) 
        { 
            call(m_seq, params); 
            return true; 
        }

    private:
        Fn m_fn;
        T *m_obj;
        typename GenSeq<sizeof...(Args)>::Type m_seq;
    };
}