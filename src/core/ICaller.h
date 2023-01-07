#pragma once

#include "Base.h"

namespace TARDIS::CORE
{
    class ICaller
    {
    public:
        virtual bool operator()(Str *params) = 0;
        virtual bool operator()(MemoryBuffer *params) = 0;
    };
}