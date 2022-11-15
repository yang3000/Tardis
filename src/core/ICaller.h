#pragma once

#include "Base.h"

namespace TARDIS::CORE
{

    class ICaller
    {
    public:
        virtual bool operator()(Str *params) = 0;
    };
}