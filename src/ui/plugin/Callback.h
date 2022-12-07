#pragma once

#include "IPlugin.h"

#include <functional>

namespace TARDIS::UI
{
    class Callback : public IPlugin
    {
    public:
        using FN = std::function<void()>;

        Callback(FN fn) : m_fn(fn) {}

        void execute() { m_fn(); }

    private:
        FN m_fn;
    };
}
