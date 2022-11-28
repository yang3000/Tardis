#pragma once

#include <memory>
#include <unordered_map>

#include <map>
#include "Base.h"
#include "Log.h"
#include "DynamicModule.h"
//#include "Plugin.h"
//#include "DynamicModuleManager.h"
//#include "FunctorContainerImpl.h"


namespace TARDIS::CORE
{
	//class PluginEventArgs : public EventArgs
	//{
	//public:
	//	PluginEventArgs(Node* inst) : instance(inst) {}
	//	Node* instance;
	//};


	class IPlugin;

	class DynamicModule;


	class PluginManager
	{
	public:
		using CreatePluginType = IPlugin * (*)(FunctorContainer*);

        struct PluginGroup
        {
            std::shared_ptr<DynamicModule> m_dyModule;
            std::vector<std::shared_ptr<IPlugin>> m_Plugins;
        };

        using PluginGroups = std::unordered_map<std::string, PluginGroup>;

		static PluginManager& Create()
		{
			if (!m_self) {
				m_self = new PluginManager();
			}
			return *m_self;
		}

		static void Destroy()
		{
			if (m_self)
			{
				m_self->releasePlugins();
				delete m_self;
			}
			m_self = nullptr;
		}

		static inline void LoadPluginFile(const std::string& name, const std::string& path)
		{
			assert(m_self);
			m_self->loadPlugin(name, path);
		}

		static inline void LoadPluginFile(const std::string& name, const std::string& path, const std::string& moduleId)
		{
			assert(m_self);
			m_self->loadPlugin(name, path, moduleId);
		}

		static inline IPlugin* CreatePlugin(const std::string& moduleId, FunctorContainer* pFunctorContainer)
		{
			assert(m_self);
			return m_self->createPlugin(moduleId, pFunctorContainer);
		}

		static inline IPlugin* GetPlugin(const std::string& instName)
		{
			assert(m_self);
			return m_self->getPlugin(instName);
		}

		static inline void DestroyPlugin(const std::string& instName)
		{
			assert(m_self);
			m_self->destroyPlugin(instName);
		}

	private:
		void loadPlugin(const std::string& name, const std::string& path);

		void loadPlugin(const std::string& name, const std::string& path, const std::string& moduleId);

		IPlugin* createPlugin(const std::string& moduleId, FunctorContainer* pFunctorContainer);

		IPlugin* getPlugin(const std::string& instName);

		void destroyPlugin(const std::string& instName);

		void releasePlugins();

		PluginManager() = default;
		PluginManager& operator=(const PluginManager&) = delete;
		PluginManager(const PluginManager&) = delete;

		PluginGroups m_pluginGroups;

		static PluginManager* m_self;
	};
}