#pragma once

#include "Base.h"

namespace TARDIS::CORE
{
    class ICaller;

    class IPlugin
    {
    public:


        virtual ICaller* getCaller(const char* fnName) = 0;

        virtual void parseCallerInfo(ParseCallBack cb) = 0;

        virtual const char* getName() = 0;

       // virtual void log(const char* msg) = 0;

        virtual void destroy() = 0;

        virtual ~IPlugin() {}
    };
}