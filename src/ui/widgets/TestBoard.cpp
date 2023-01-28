#include "TestBoard.h"

#include "../imgui/imgui.h"

#include "Engine.h"

namespace TARDIS::UI
{
    TestBoard::TestBoard()
        : m_content()
    {
        m_engine    = std::make_shared<CORE::Engine>("TestEngine");
        m_plugin_cb = std::make_shared<CORE::CallBackImpl>(m_engine);

        
        CORE::PluginManager::LoadPluginEvent.addListener([this](uint64_t pluginId, std::shared_ptr<CORE::PluginContainer> container)
        {
            // 全局插件->所有Engine拥有同一个插件实例
            if(container->isGlobal())
            {
                if(container->isEmpty())
                {
                    container->create();
                }
                auto newPlugin = container->get(0);
                m_engineSetup->addPlugin(pluginId, newPlugin);
                m_engineRunTest->addPlugin(pluginId, newPlugin);
                return;
            }

            // 线程插件->每个Engine创建一个新的插件实例
            auto plugin = m_engineRunTest->addPlugin(pluginId);
            if(plugin)
            {
                plugin->setCallback(m_plugin_cb.get());     
                plugin->setLogger(m_plugin_log.get());   
                plugin->loadCallers();
                m_engineSetup->addPlugin(pluginId, plugin);
            }
        });
    }

    void TestBoard::drawImpl()
    {
        ImGui::Text(m_content.c_str());
    }
}