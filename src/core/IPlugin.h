#pragma once

#include "Base.h"

namespace TARDIS::CORE
{

    struct VCallBack
    {
        virtual void addPoolData(const char* key, const char* value) = 0;
        virtual void addOutput(const char* key, const char* value) = 0;
    };

    //typedef void (*AddPoolData)(const char* key, const char* value);

    class ICaller;

    class Log;

    class IPlugin
    {
    public:
        virtual void setLogger(Log* logger) = 0;

        virtual bool initialize() = 0;

        virtual ICaller* getCaller(const char* fnName) = 0;

        virtual void parseCallerInfo(ParseCallBack cb) = 0;

        virtual const char* getName() = 0;

        virtual void setCallback(VCallBack* cb) = 0;

        virtual void destroy() = 0;

        virtual ~IPlugin() {}
    };
}