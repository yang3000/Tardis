#pragma once

#include <vector>

#include "IPlugin.h"

namespace TARDIS::UI
{

	class Pluginable
	{
	public:
		~Pluginable()
		{
			removeAllPlugins();
		}

		template<typename T, typename... Args>
		T& addPlugin(Args&& ... p_args)
		{
			static_assert(std::is_base_of<IPlugin, T>::value, "T should derive from IPlugin");

			T* newPlugin = new T(std::forward<Args>(p_args)...);
			m_plugins.push_back(newPlugin);
            
			return *newPlugin;
		}

		template<typename T>
		T* getPlugin()
		{
			static_assert(std::is_base_of<IPlugin, T>::value, "T should derive from IPlugin");

			for (auto it = m_plugins.begin(); it != m_plugins.end(); ++it)
			{
				T* result = dynamic_cast<T*>(*it);
				if (result)
					return result;
			}

			return nullptr;
		}

		void executePlugins()
		{
			for (auto& plugin : m_plugins)
				plugin->execute();
		}

		void removeAllPlugins()
		{
			for (auto& plugin : m_plugins)
				delete plugin;

			m_plugins.clear();
		}

	private:
		std::vector<IPlugin*> m_plugins;
	};
}