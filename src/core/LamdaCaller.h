#pragma once

#include "Base.h"
#include "ICaller.h"
#include "ValueHelper.h"
#include <string>
#include <assert.h>

namespace TARDIS::CORE
{
    // 实现从任意lamda表达式到bool(*)(Str* params)的转化
    template <typename Fn, typename R, typename... Args>
    class LamdaCaller : public ICaller
    {
    public:
        LamdaCaller(Fn fn) : m_fn(fn) {}

        template <int... S>
        R call(Seq<S...>, Str *params) { return m_fn(ValueHelper<Args>::from(std::string(params[S].buf, params[S].len))...); }

        bool operator()(Str *params)
        {
            R res = call(m_seq, params);
            return true;
        }

    private:
        Fn  m_fn;
        typename GenSeq<sizeof...(Args)>::Type m_seq;
    };
}