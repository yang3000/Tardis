#pragma once


#include "IPlugin.h"
#include "fmt/core.h"
#include <string>
#include <assert.h>
#include "CallerContainer.h"
#include "Log.h"
#include "Communication.h"

#define LOG_TRACE(...)       do { m_logger ? m_logger->log(TARDIS::CORE::LogType::Trace,    fmt::format(__VA_ARGS__).c_str()) : void(0); } while (false)
#define LOG_INFO(...)        do { m_logger ? m_logger->log(TARDIS::CORE::LogType::Info,     fmt::format(__VA_ARGS__).c_str()) : void(0); } while (false)
#define LOG_WARN(...)        do { m_logger ? m_logger->log(TARDIS::CORE::LogType::Warn,     fmt::format(__VA_ARGS__).c_str()) : void(0); } while (false)
#define LOG_ERROR(...)       do { m_logger ? m_logger->log(TARDIS::CORE::LogType::Error,    fmt::format(__VA_ARGS__).c_str()) : void(0); } while (false)
#define LOG_CRITICAL(...)    do { m_logger ? m_logger->log(TARDIS::CORE::LogType::Critical, fmt::format(__VA_ARGS__).c_str()) : void(0); } while (false)

#define RegisterFunctor(...) m_callerContainer->registerFunctor(__VA_ARGS__);

namespace TARDIS::CORE
{
    template<typename T>
    class Plugin : public IPlugin
    {
    public:
        Plugin(std::string name);

        ~Plugin();

        static T *CreateInstance(const std::string& name) 
        { 
            //static_assert(std::is_base_of<Plugin, T>::value, "T should derive from Plugin");
            return new T(name); 
        }

        void setLogger(Log *logger) override;

        bool loadCallers() override;

        ICaller* getCaller(const char* fnName) override;

        void parseCallerInfo(ParseCallBack cb) override;

        void setCallback(VCallBack* cb) override;

        const char *getName() override;

        IPlugin* clone() override;

        void destroy() override;

        void addPoolData(const char* key, const char* value);

        void addOutput(const char *key, const char *value);

        void showTestItem(const char* name, bool res, const char* value, const char* lower, const char* upper, const char* desc);

        void showTestItem(const char* name, bool res = true, const char* desc = nullptr);

        template<typename DataType>
        void showTestItem(const char* name, DataType value, decltype(value) lower, decltype(value) upper, const char* desc = nullptr)
        {
            bool res = (value < lower || value >  upper);
            showTestItem(
                name, 
                !res, 
                ValueHelper<DataType>::toString(value).c_str(), 
                ValueHelper<DataType>::toString(lower).c_str(), 
                ValueHelper<DataType>::toString(upper).c_str(), 
                desc
            );
        }

        Communication* getCommunication(uint64_t moduleId);

    protected:
        Log *m_logger;

        CallerContainer *m_callerContainer;

    private:
        IPlugin *m_self;

        VCallBack* m_pFn;

        std::string m_name;

    };
}

#include "Plugin.inl"
