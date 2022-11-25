#pragma once


#include "IPlugin.h"
#include "fmt/core.h"
#include <string>
#include <assert.h>
#include "CallerContainer.h"
#include "Log.h"
#include "Communication.h"

namespace TARDIS::CORE
{
    class Plugin : public IPlugin
    {
    public:
        Plugin(std::string name);

        ~Plugin()
        {
            printf("plugin[%s] is destroyed.\r\n", m_name.c_str());
            delete m_callerContainer;

        };

        template <typename T>
        static T *CreateInstance(const std::string& name) { return new T(name); }
    
        template <typename... Args>
        void registerFunctor(const char* name, const std::vector<ParamInfo>& paramData, Args&&... args)
        {
            m_callerContainer->registerFunctor(name, std::forward<Args>(args)..., paramData);
        }

        ICaller* getCaller(const char* fnName) { return m_callerContainer->get(fnName)->caller; }

        virtual void parseCallerInfo(ParseCallBack cb) override;

        void setCallback(VCallBack* cb) { assert(cb); m_pFn = cb; }

        void setLogger(Log *logger) { m_logger = logger; }

        bool loadCallers() { return true; }

        const char *getName() { return m_name.c_str(); }

        void destroy() { delete m_self; }

        void addPoolData(const char* key, const char* value) 
        { 
            assert(m_pFn); 
            m_pFn->addPoolData(key, value);
        }

        void addOutput(const char *key, const char *value)
        {
            assert(m_pFn);
            m_pFn->addOutput(key, value);
        }

        Communication* getCommunication(const char *moduleId)
        {
            assert(m_pFn);
            Communication* pCommu = m_pFn->getCommunication(moduleId);
            if(!pCommu)
            {
                //throw 
            }
            return pCommu;
        }

    protected:
        Log *m_logger;
        CallerContainer *m_callerContainer;
    private:
        IPlugin *m_self;

        VCallBack* m_pFn;

        std::string m_name;
    };
}

#define LOG_TRACE(...)       do { m_logger ? m_logger->log(TARDIS::CORE::LogType::Trace,    fmt::format(__VA_ARGS__).c_str()) : void(0); } while (false)
#define LOG_INFO(...)        do { m_logger ? m_logger->log(TARDIS::CORE::LogType::Info,     fmt::format(__VA_ARGS__).c_str()) : void(0); } while (false)
#define LOG_WARN(...)        do { m_logger ? m_logger->log(TARDIS::CORE::LogType::Warn,     fmt::format(__VA_ARGS__).c_str()) : void(0); } while (false)
#define LOG_ERROR(...)       do { m_logger ? m_logger->log(TARDIS::CORE::LogType::Error,    fmt::format(__VA_ARGS__).c_str()) : void(0); } while (false)
#define LOG_CRITICAL(...)    do { m_logger ? m_logger->log(TARDIS::CORE::LogType::Critical, fmt::format(__VA_ARGS__).c_str()) : void(0); } while (false)