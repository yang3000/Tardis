#pragma once

#include "Base.h"

typedef void (*ParseCallBack)(const char *, Param *, unsigned);

namespace TARDIS
{
    class Communication;
    namespace CORE
    {
        class ICaller;
        class Log;
    }
}

struct CallerParameters
{
    CChar name;
    Param *params;
    UInt count;
};

namespace TARDIS::CORE
{
    struct VCallBack
    {
        virtual void addPoolData(const char* key, const char* value) = 0;

        virtual void output(const char* value) = 0;

        // inside plugin can use this function to show test message on ui.
        virtual void showTestItem(
            const char* name, 
            bool  res = true,
            const char* value = nullptr, 
            const char* lower = nullptr, 
            const char* upper = nullptr, 
            const char* desc = nullptr
            ) = 0;

        virtual Communication* getCommunication(uint64_t moduleId) = 0;
    };

    class IPlugin
    {
    public:
        virtual void setLogger(Log* logger) = 0;

        virtual bool loadCallers() = 0;

        virtual ICaller* getCaller(const char* fnName) = 0;

        virtual void parseCallerInfo(ParseCallBack cb) = 0;

        virtual const char* getName() = 0;

        virtual void setCallback(VCallBack* cb) = 0;

        virtual IPlugin* clone() = 0;

        virtual void destroy() = 0;

        virtual ~IPlugin() {}
    };
}