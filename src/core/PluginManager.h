#pragma once

#include <memory>
#include <unordered_map>
#include <map>

#include "Base.h"
#include "Log.h"
#include "DynamicModule.h"
#include "RapidJsonParser.h"
#include "Event.h"
//#include "Plugin.h"
//#include "DynamicModuleManager.h"
//#include "FunctorContainerImpl.h"

namespace TARDIS
{
    class DynamicModule;
}
namespace TARDIS::CORE
{
    class IPlugin;
    class PluginContainer
    {
    public:
        PluginContainer(const std::string &name, const std::string &path);

        ~PluginContainer();

        IPlugin* get();

        CChar getName();

    private:
        // no copy, no assignment
        PluginContainer(const PluginContainer&) = delete;
        PluginContainer& operator=(const PluginContainer&) = delete;

    private:
        std::string                    m_name;
        std::shared_ptr<DynamicModule> m_dyModule;
        std::vector<IPlugin*>          m_Plugins;
    };

    class PluginManager
    {
    public:
        static inline bool OnDeserialize(std::shared_ptr<CORE::RapidJsonParser> json_node);

        static inline void LoadPlugin(const std::string &name, const std::string &path, uint64_t id = 0);

        static inline CChar GetPluginName(uint64_t id);

        static inline IPlugin *CreatePlugin(const uint64_t id);

        static inline void DestroyPlugin(const uint64_t id);

        static inline void DestroyAllPlugins();

    public:
        static Event<uint64_t> LoadPluginEvent;

    private:
        PluginManager() = delete;
        PluginManager &operator=(const PluginManager &) = delete;
        PluginManager(const PluginManager &) = delete;
    
        static uint64_t ID_INCREMENT;
        using  PluginContainers = std::unordered_map<uint64_t, std::unique_ptr<PluginContainer>>;
        static PluginContainers m_sPluginContainers;
    };

    bool PluginManager::OnDeserialize(std::shared_ptr<CORE::RapidJsonParser> json_node)
    {
        if (json_node->nodeBegin("modules"))
			{
				if (json_node->is<rapidjson::Value::Array>())
				{
					for (int i = 0; i < json_node->size(); i++)
					{
						if (json_node->nodeBegin(std::to_string(i)))
                        {
                            std::string name = json_node->get<std::string>("name");
                            std::string path = json_node->get<std::string>("path");
                            uint64_t id      = json_node->get<uint64_t>("module_id");
                            LoadPlugin(name, path, id);

                            LoadPluginEvent.invoke(id);

                            json_node->nodeEnd();
                        };
					}
				}
				json_node->nodeEnd();
			}
            return true;
    }

    void PluginManager::LoadPlugin(const std::string &name, const std::string &path, uint64_t id)
    {
        if (id > ID_INCREMENT)
        {
            ID_INCREMENT = id;
        }
        uint64_t tId = (id == 0) ? ++ID_INCREMENT : id;
        if (!m_sPluginContainers.count(tId))
        {
            m_sPluginContainers.emplace(tId, std::make_unique<PluginContainer>(name, path));
        }
    }

    IPlugin *PluginManager::CreatePlugin(const uint64_t id)
    {
        auto it = m_sPluginContainers.find(id);
        if (it != m_sPluginContainers.end())
        {
            return it->second->get();
        }
        return nullptr;
    }

    CChar PluginManager::GetPluginName(uint64_t id)
    {
        auto it = m_sPluginContainers.find(id);
        if (it != m_sPluginContainers.end())
        {
            return it->second->getName();
        }
        return nullptr;
    }


    void PluginManager::DestroyPlugin(const uint64_t id)
    {
        auto it = m_sPluginContainers.find(id);
        if (it != m_sPluginContainers.end())
        {
            m_sPluginContainers.erase(it);
        }
    }

    void PluginManager::DestroyAllPlugins()
    {
        m_sPluginContainers.clear();
    }
}