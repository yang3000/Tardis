#pragma once

namespace TARDIS::CORE
{
    enum class LogType
    {
        Trace = 0,
        Info,
        Warn,
        Error,
        Critical
    };

    class Log
    {
    public:
        virtual void log(LogType type, const char *msg) = 0;

        virtual ~Log() {};
    };
}

// #define LOG_TRACE(obj, msg)      obj->log(LogType::Trace, msg)
// #define LOG_INFO(obj, msg)       obj->log(LogType::Info, msg)
// #define LOG_WARN(obj, msg)       obj->log(LogType::Warn, msg)
// #define LOG_ERROR(obj, msg)      obj->log(LogType::Error, msg)
// #define LOG_CRITICAL(obj, msg)   obj->log(LogType::Critical, msg)



