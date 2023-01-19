#include "PanelTestStand.h"

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
    // void PanelTestStand::TestStatusButton(const char *id, const ImVec4 &color, bool running)
    // {
    //     ImGuiContext &g = *GImGui;
    //     ImGui::ColorButton(id, color, ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoBorder);
    //     if (running)
    //     {
    //         ImVec2 center = g.LastItemData.Rect.GetCenter();
    //         float radius = ImFloor(ImMin(g.LastItemData.Rect.GetWidth(), g.LastItemData.Rect.GetHeight()) * 0.40f);
    //         float t = (float)(ImGui::GetTime() * 10.0f);
    //         ImVec2 off(ImCos(t) * radius, ImSin(t) * radius);
    //         ImGui::GetWindowDrawList()->AddLine(center - off, center + off, ImGui::GetColorU32(ImGuiCol_Text), 1.5f);
    //     }
    // }

    PanelTestStand::PanelTestStand()
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

    PanelTestStand::~PanelTestStand()
    {
        CORE::PluginManager::DestroyAllPlugins();
    }

    void PanelTestStand::onAddTestResult(CORE::TestItemResult* result)
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
        ImGui::Begin("Sequence Editor");
        const float TEXT_BASE_HEIGHT = ImGui::GetTextLineHeightWithSpacing();

        if (m_engineIsRunning)
        {
            ImGui::BeginDisabled();
        }

        if (ImGui::Button(ICON_FA_PLAY, ImVec2(TEXT_BASE_HEIGHT + 16.0f, TEXT_BASE_HEIGHT + 16.0f)))
        {
            m_testItemList.clear();
            m_engineRunTest->runTask();
        }

        if (m_engineIsRunning)
        {
            ImGui::EndDisabled();
        }

        //const float   headerHeight = ImGui::GetFrameHeight();
        const float   headerHeight = ImGui::GetFrameHeightWithSpacing();
        //ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, cell_padding);
        ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(4, 2) * 1.0f);
        static ImGuiTableFlags flagsSequence = ImGuiTableFlags_BordersV | /* ImGuiTableFlags_ScrollY | */ ImGuiTableFlags_Resizable |  ImGuiTableFlags_NoBordersInBody | ImGuiTableFlags_SizingFixedFit;

        if (ImGui::BeginTable("Sequences", 7,  flagsSequence))
        {
            ImGui::TableSetupScrollFreeze(0, 1);
            ImGui::TableSetupColumn("Index");
            ImGui::TableSetupColumn("Item");
            ImGui::TableSetupColumn("Desc");
            ImGui::TableSetupColumn("Lower");
            ImGui::TableSetupColumn("Value");
            ImGui::TableSetupColumn("Upper");
            ImGui::TableSetupColumn("Result",ImGuiTableColumnFlags_WidthStretch);

            ImGui::TableHeadersRow();

            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(6, 4) * 1.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(3, 0) * 1.0f);
            
            static int seleted_col = -1;
            for (int i = 0; i < m_testItemList.size(); ++i)
            {
                ImGui::TableNextRow(ImGuiTableRowFlags_None);
                ImGui::PushID(("test_stand_" + std::to_string(i)).c_str());

                ImVec4 status_color  = ImVec4(0.8f, 0.4f, 0.1f, 1.0f);

                ImGui::TableNextColumn();
                ImGui::Selectable(std::to_string(i + 1).c_str(), false, ImGuiSelectableFlags_SpanAllColumns);

                ImGui::TableNextColumn();
                ImGui::Text(m_testItemList[i]->name.c_str());

                ImGui::TableNextColumn();
                ImGui::Text(m_testItemList[i]->desc.c_str());

                ImGui::TableNextColumn();
                ImGui::Text(m_testItemList[i]->lower.c_str());

                ImGui::TableNextColumn();
                ImGui::Text(m_testItemList[i]->value.c_str());

                ImGui::TableNextColumn();
                ImGui::Text(m_testItemList[i]->upper.c_str());
              
                ImGui::TableNextColumn();
                ImGui::TextUnformatted("==");

                ImGui::PopID();
            }

            ImGui::Spacing();
            ImGui::Spacing();
            ImGui::PopStyleVar(2);
            ImGui::EndTable();
        }
        

        // static ImGuiTableFlags flags = 
        // ImGuiTableFlags_Borders | 
        // ImGuiTableFlags_ScrollY |
        // ImGuiTableFlags_RowBg | 
        // ImGuiTableFlags_BordersOuterH | 
        // ImGuiTableFlags_BordersInnerH | 
        // ImGuiTableFlags_BordersV | 
        // ImGuiTableFlags_BordersOuterV | 
        // ImGuiTableFlags_BordersInnerV | 
        // ImGuiTableFlags_BordersOuter | 
        // ImGuiTableFlags_BordersInner | 
        // ImGuiTableFlags_BordersH;

        // if (ImGui::BeginTable("table1", 3, flags))
        // {
        //     ImGui::TableSetupColumn("One");
        //     ImGui::TableSetupColumn("Two");
        //     ImGui::TableSetupColumn("Three");
        //     ImGui::TableHeadersRow();
        //     for (int row = 0; row < 4; row++)
        //     {
        //         ImGui::TableNextRow();
        //         for (int column = 0; column < 3; column++)
        //         {
        //             ImGui::TableSetColumnIndex(column);
        //             ImGui::Text("Row %d Column %d", row, column);
        //         }
        //     }
        //     ImGui::EndTable();
        // }

        ImGui::PopStyleVar();

        ImGui::End();

    }
}