#pragma once

#include "Base.h"
#include "ICaller.h"
#include "ValueHelper.h"
#include <string>
#include <functional>

namespace TARDIS::CORE
{
    // 实现从任意自由函数到bool(*)(Str* params)的转化
    template <typename R, typename... Args>
    class FreeCaller : public ICaller
    {
    public:
        using Fn = std::function<R(Args...)>;

        FreeCaller(Fn fn) : m_fn(fn) {}

        template <int... S>
        R call(Seq<S...>, Str *params) 
        { 
            return m_fn(ValueHelper<Args>().from(std::string(params[S].buf, params[S].len))...); 
        }

        bool operator()(Str *params)
        {
            R res = call(m_seq, params);
            return !!res;
        }

        template <int... S> 
        R call(Seq<S...>, MemoryBuffer *params) 
        { 
            return m_fn(ValueHelper<Args>::from(params[S])...); 
        }

        bool operator()(MemoryBuffer *params) 
        { 
            R res = call(m_seq, params);
            return !!res;
        }

    private:
        Fn m_fn;
        typename GenSeq<sizeof...(Args)>::Type m_seq;
    };

    // 实现从任意自由函数到bool(*)(Str* params)的转化
    // 针对返回值为void类型的任意函数的偏特化
    template <typename... Args>
    class FreeCaller<void, Args...> : public ICaller
    {
    public:
        using Fn = std::function<void(Args...)>;

        FreeCaller(Fn fn) : m_fn(fn) {}

        template <int... S>
        void call(Seq<S...>, Str *params) 
        { 
            m_fn(ValueHelper<Args>::from(std::string(params[S].buf, params[S].len))...); 
        }

        bool operator()(Str *params)
        {
            call(m_seq, params);
            return true;
        }

        template <int... S> 
        void call(Seq<S...>, MemoryBuffer *params) 
        { 
             m_fn(ValueHelper<Args>::from(params[S])...); 
        }

        bool operator()(MemoryBuffer *params) 
        { 
            call(m_seq, params);
            return true;
        }

    private:
        Fn m_fn;
        typename GenSeq<sizeof...(Args)>::Type m_seq;
    };
}