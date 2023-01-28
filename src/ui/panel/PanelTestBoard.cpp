#include "PanelTestBoard.h"

#define IMGUI_DEFINE_MATH_OPERATORS
#include "../imgui/imgui.h"
#include "../imgui/imgui_internal.h"
#include "IconsFontAwesome5.h"

#include "Engine.h"
#include "RapidJsonParser.h"
#include "Engine.h"
#include "PluginManager.h"
#include "SpdLog.h"

namespace TARDIS::UI
{
    PanelTestBoard::PanelTestBoard()
    {
        CORE::SpdLog::DefaultLogger();

        m_engineIsRunning = false;

        m_engineRunTest   = std::make_shared<CORE::Engine>("TaskEngine");
        m_engineSetup     = std::make_shared<CORE::Engine>("GlobalSetup");
        m_engineCleanup   = std::make_shared<CORE::Engine>("GlobalCleanup");
         
        m_plugin_cb       = std::make_shared<CORE::CallBackImpl>(m_engineRunTest);
        m_plugin_cb->addPoolData("imei", "yansahjhsdafsd");
        m_plugin_log      = std::make_shared<CORE::SpdLog>("", "", true);
 
        m_globalPluginLog = std::make_shared<CORE::SpdLog>("Tardis_Log", "tardis_default.log");
 
        m_json_parser     = std::make_shared<CORE::RapidJsonParser>();

        m_json_parser->parseJsonFile("sequence.json");

        TDS_LOG_INFO(m_json_parser->get("version"));

        m_engineRunTest->RunnerFinishEvent.addListener(std::bind(&PanelTestStand::onAddTestResult, this, std::placeholders::_1));

        m_engineRunTest->EngineBeginEvent.addListener([this]{ m_engineIsRunning = true;});
        m_engineRunTest->EngineEndEvent.addListener([this]{ m_engineIsRunning = false;});

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

        CORE::PluginManager::OnDeserialize(m_json_parser);
        CORE::Engine::OnDeserialize(m_json_parser);

    }

    PanelTestBoard::~PanelTestBoard()
    {
        CORE::PluginManager::DestroyAllPlugins();
    }

    void PanelTestBoard::onAddTestResult(CORE::TestItemResult* result)
    {
        auto res = m_testItemList.emplace_back(std::make_shared<CORE::TestItemResult>());
        res->name   = result->name;
        res->desc   = result->desc;
        res->lower  = result->lower;
        res->value  = result->value;
        res->upper  = result->upper;
        res->result = result->result;
    }

    void PanelTestStand::drawImpl()
    {
        
    }
}