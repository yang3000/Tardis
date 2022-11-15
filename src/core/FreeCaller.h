#pragma once

#include "Base.h"
#include "ICaller.h"
#include "ValueHelper.h"
#include <string>

namespace TARDIS::CORE
{
    // 实现从任意自由函数到bool(*)(Str* params)的转化
    template <typename R, typename... Args>
    class FreeCaller : public ICaller
    {
    public:
        using Fn = R (*)(Args...);

        FreeCaller(Fn fn) : m_fn(fn) {}

        template <int... S>
        R call(Seq<S...>, Str *params) { return m_fn(ValueHelper<Args>::fromString(std::string(params[S].buf, params[S].len))...); }

        bool operator()(Str *params)
        {
            R res = call(m_seq, params);
            return true;
        }

    private:
        Fn m_fn;
        typename GenSeq<sizeof...(Args)>::Type m_seq;
    };
}