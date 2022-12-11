#include "PluginManager.h"

#include "DynamicModule.h"
#include "IPlugin.h"

typedef TARDIS::CORE::IPlugin *(*CreatePlugin)();

namespace TARDIS::CORE
{
    
    PluginContainer::PluginContainer(const std::string &name, const std::string &path)
        : m_name(name)
        , m_dyModule(std::make_shared<DynamicModule>(path))
    { 
        printf("load plugin,name:%s,path:%s\r\n", name.c_str(), path.c_str());
    }

    PluginContainer::~PluginContainer()
    {
        printf("PluginContainer is destroy, name:%s\r\n", m_name.c_str());
        for (auto p : m_Plugins)
        {
            p->destroy();
        }
        m_Plugins.clear();
    }

    IPlugin* PluginContainer::get()
    {
        m_Plugins.emplace_back(m_dyModule->Call<CreatePlugin>("CreatePlugin"));
        return m_Plugins.back();
    }

    CChar PluginContainer::getName()
    {
        return m_name.c_str();
    }

	uint64_t PluginManager::ID_INCREMENT = 0;

    Event<uint64_t> PluginManager::LoadPluginEvent;

    PluginManager::PluginContainers PluginManager::m_sPluginContainers;
}