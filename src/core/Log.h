#pragma once

namespace TARDIS::CORE
{
    enum LogType
    {
        TRACE,
        INFO,
        WARN,
        ERROR,
        CRITICAL
    };

    class Log
    {
    public:
        virtual void log(LogType type, const char *msg) = 0;

        virtual ~Log() {};
    };
}