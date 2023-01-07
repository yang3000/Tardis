#include "PluginManager.h"

#include "DynamicModule.h"
#include "IPlugin.h"

typedef TARDIS::CORE::IPlugin *(*CreatePlugin)();

namespace TARDIS::CORE
{
    
    PluginContainer::PluginContainer(const std::string &name, const std::string &path, const std::string &desc, bool global)
        : m_name(name)
        , m_dyModule(std::make_shared<DynamicModule>(path))
        , m_desc(desc)
        , m_global(global)

    { 
        printf("load plugin->\r\nname:%s\r\npath:%s\r\n", name.c_str(), path.c_str());
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

    IPlugin* PluginContainer::create()
    {
        m_Plugins.emplace_back(m_dyModule->Call<CreatePlugin>("CreatePlugin"));
        return m_Plugins.back();
    }

    IPlugin *PluginContainer::get(int idx)
    {
        if (idx < m_Plugins.size())
        {
            return m_Plugins[idx];
        }
        return nullptr;
    }

    CChar PluginContainer::getName()
    {
        return m_name.c_str();
    }

    CChar PluginContainer::getFilePath()
    {
        return m_dyModule->getModulePath().c_str();
    }

    std::string& PluginContainer::getDesc()
    {
        return m_desc;
    }

    bool PluginContainer::isGlobal()
    {
        return m_global;
    }

    bool PluginContainer::isEmpty()
    {
        return m_Plugins.empty();
    }

    uint64_t PluginManager::ID_INCREMENT = 0;

    Event<uint64_t, std::shared_ptr<PluginContainer>> PluginManager::LoadPluginEvent;

    PluginManager::PluginContainers PluginManager::m_sPluginContainers;
}