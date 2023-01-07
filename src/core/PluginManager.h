#pragma once

#include <memory>
#include <unordered_map>
#include <map>

#include "Base.h"
#include "Log.h"
#include "DynamicModule.h"
#include "RapidJsonParser.h"
#include "Event.h"
#include "ValueHelper.h"
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
        PluginContainer(const std::string &name, const std::string &path, const std::string &desc = "", bool global = false);

        ~PluginContainer();

        IPlugin* create();

        IPlugin* get(int idx);

        CChar getName();

        CChar getFilePath();

        std::string& getDesc();

        bool  isGlobal();

        bool  isEmpty();

    private:
        // no copy, no assignment
        PluginContainer(const PluginContainer&) = delete;
        PluginContainer& operator=(const PluginContainer&) = delete;

    private:
        std::string                    m_name;
        std::string                    m_desc;
        std::shared_ptr<DynamicModule> m_dyModule;
        std::vector<IPlugin*>          m_Plugins;
        bool                           m_global;
    };

    class PluginManager
    {
    public:
        using  PluginContainers = std::unordered_map<uint64_t, std::shared_ptr<PluginContainer>>;

        static inline bool OnDeserialize(std::shared_ptr<CORE::RapidJsonParser> json_node);

        static inline bool OnSerialize(CORE::RapidJsonParser::Writer& json_writer);

        static inline void LoadPlugin(const std::string &name, const std::string &path, const std::string &desc = "", bool global = false, uint64_t id = 0);

        static inline CChar GetPluginName(uint64_t id);

        static inline IPlugin *CreatePlugin(const uint64_t id);

        static inline PluginContainers& GetPlugins();

        static inline void ClonePlugin(const uint64_t id);

        static inline void DestroyPlugin(const uint64_t id);

        static inline void DestroyAllPlugins();

    public:
        static Event<uint64_t, std::shared_ptr<PluginContainer>> LoadPluginEvent;

    private:
        PluginManager() = delete;
        PluginManager &operator=(const PluginManager &) = delete;
        PluginManager(const PluginManager &) = delete;
    
        static uint64_t ID_INCREMENT;

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
                        std::string name   = json_node->get<std::string>("name");
                        std::string path   = json_node->get<std::string>("path");
                        std::string desc   = json_node->get<std::string>("desc");
                        uint64_t    id     = json_node->get<uint64_t>("module_id");
                        bool        global = json_node->get<bool>("global");

                        LoadPlugin(name, path, desc, global, id);
                        json_node->nodeEnd();
                    };
                }
            }
            json_node->nodeEnd();
        }
        return true;
    }

    bool PluginManager::OnSerialize(CORE::RapidJsonParser::Writer &json_writer)
    {
        json_writer.Key("modules");
        json_writer.StartArray();
        for (auto &[id, container] : m_sPluginContainers)
        {
            json_writer.StartObject();

            json_writer.Key("name");      json_writer.String(container->getName());
            json_writer.Key("module_id"); json_writer.Int64(id);
            json_writer.Key("path");      json_writer.String(container->getFilePath());
            json_writer.Key("desc");      json_writer.String(container->getDesc());

            json_writer.EndObject();
        }

        json_writer.EndArray();
        return true;
    }

    void PluginManager::LoadPlugin(const std::string &name, const std::string &path, const std::string &desc, bool global, uint64_t id)
    {
        if (id > ID_INCREMENT)
        {
            ID_INCREMENT = id;
        }
        uint64_t tId = (id == 0) ? ++ID_INCREMENT : id;
        if (!m_sPluginContainers.count(tId))
        {
            auto container = std::make_shared<PluginContainer>(name, path, desc, global);
            m_sPluginContainers.emplace(tId, container);
            LoadPluginEvent.invoke(tId, container);
        }
    }

    IPlugin *PluginManager::CreatePlugin(const uint64_t id)
    {
        auto it = m_sPluginContainers.find(id);
        if (it != m_sPluginContainers.end())
        {
            return it->second->create();
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

    PluginManager::PluginContainers& PluginManager::GetPlugins()
    {
        return m_sPluginContainers;
    }

    void PluginManager::ClonePlugin(const uint64_t id)
    {
        auto it = m_sPluginContainers.find(id);
        if (it != m_sPluginContainers.end())
        {
            LoadPlugin(std::string(it->second->getName()) + "_Cloned", it->second->getFilePath(), it->second->getDesc());
        }
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