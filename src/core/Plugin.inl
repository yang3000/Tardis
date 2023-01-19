#include "Plugin.h"
#include "CallerContainer.h"
#include "ValueHelper.h"

namespace TARDIS::CORE
{
    template <typename T>
    Plugin<T>::Plugin(std::string name)
        : m_logger(nullptr)
        , m_callerContainer(new CallerContainer())
        , m_self(this)
        , m_pFn(nullptr)
        , m_name(std::move(name))
    {};

    template <typename T>
    Plugin<T>::~Plugin()
    {
        LOG_INFO("plugin{} is destroyed", m_name);
        delete m_callerContainer;
    };

    template <typename T>
    ICaller *Plugin<T>::getCaller(const char *fnName) 
    { 
        return m_callerContainer->get(fnName)->caller; 
    }

    template <typename T>
    void Plugin<T>::parseCallerInfo(ParseCallBack cb)
    {
        for (auto it : m_callerContainer->m_slots)
        {
            auto callerParams = it.second->params;

            Param *param = new Param[callerParams.size()];

            for (int i = 0; i < callerParams.size(); ++i)
            {
                param[i].name   = {callerParams[i].m_name.c_str(), (unsigned)callerParams[i].m_name.size()};
                param[i].type   = {callerParams[i].m_type.c_str(), (unsigned)callerParams[i].m_type.size()};
                param[i].typeId = {callerParams[i].m_typeId.c_str(), (unsigned)callerParams[i].m_typeId.size()};
                param[i].desc   = {callerParams[i].m_desc.c_str(), (unsigned)callerParams[i].m_desc.size()};
            }

            cb(it.second->name.c_str(), param, callerParams.size());

            delete[] param;
        }
    }

    template <typename T>
    void Plugin<T>::setCallback(VCallBack *cb)
    {
        assert(cb);
        m_pFn = cb;
    }

    template <typename T>
    void Plugin<T>::setLogger(Log *logger)
    {
        m_logger = logger;
    }

    template <typename T>
    bool Plugin<T>::loadCallers()
    {
        return true;
    }

    template <typename T>
    const char *Plugin<T>::getName()
    {
        return m_name.c_str();
    }

    template <typename T>
    IPlugin *Plugin<T>::clone()
    {
        LOG_INFO("plugin:{} was cloned", m_name);
        return CreateInstance(m_name.c_str());
    }

    template <typename T>
    void Plugin<T>::destroy()
    {
        if (m_self)
        {
            delete m_self;
            m_self = nullptr;
        }
    }

    template <typename T>
    void Plugin<T>::addPoolData(const char *key, const char *value)
    {
        assert(m_pFn);
        m_pFn->addPoolData(key, value);
    }

    template <typename T>
    void Plugin<T>::output(const char *value)
    {
        assert(m_pFn);
        m_pFn->output(value);
    }

    template <typename T>
    void Plugin<T>::showTestItem(const char *name, bool res, const char *value, const char *lower, const char *upper, const char *desc)
    {
        assert(m_pFn);
        LOG_INFO("{}-{}-{}-{}-{}-{}", name, res, value ? value : "", lower ? lower : "", upper ? upper : "",desc ? desc : "");
        m_pFn->showTestItem(name, res, value, lower, upper, desc);
    }

    template <typename T>
    void Plugin<T>::showTestItem(const char *name, bool res, const char *desc)
    {
        showTestItem(name, res, nullptr, nullptr, nullptr, desc);
    }

    template <typename T>
    Communication *Plugin<T>::getCommunication(uint64_t moduleId)
    {
        assert(m_pFn);
        Communication *pCommu = m_pFn->getCommunication(moduleId);
        if (!pCommu)
        {
            // throw
        }
        return pCommu;
    }

}