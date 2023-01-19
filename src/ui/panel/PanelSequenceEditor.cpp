#include "PanelSequenceEditor.h"

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
    void PanelSequenceEditor::TestStatusButton(const char *id, const ImVec4 &color, bool running)
    {
        ImGuiContext &g = *GImGui;
        ImGui::ColorButton(id, color, ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoBorder);
        if (running)
        {
            ImVec2 center = g.LastItemData.Rect.GetCenter();
            float radius = ImFloor(ImMin(g.LastItemData.Rect.GetWidth(), g.LastItemData.Rect.GetHeight()) * 0.40f);
            float t = (float)(ImGui::GetTime() * 10.0f);
            ImVec2 off(ImCos(t) * radius, ImSin(t) * radius);
            ImGui::GetWindowDrawList()->AddLine(center - off, center + off, ImGui::GetColorU32(ImGuiCol_Text), 1.5f);
        }
    }

    PanelSequenceEditor::PanelSequenceEditor()
    {
        CORE::SpdLog::DefaultLogger();

        m_engineRunTest   = std::make_shared<CORE::Engine>("testEngine");
        m_engineSetup     = std::make_shared<CORE::Engine>("GlobalSetup");
        m_engineCleanup   = std::make_shared<CORE::Engine>("GlobalCleanup");
         
        m_plugin_cb       = std::make_shared<CORE::CallBackImpl>(m_engineRunTest);
        m_plugin_cb->addPoolData("imei", "yansahjhsdafsd");
        m_plugin_log      = std::make_shared<CORE::SpdLog>("", "", true);
 
        m_globalPluginLog = std::make_shared<CORE::SpdLog>("Tardis_Log", "tardis_default.log");
 
        m_json_parser     = std::make_shared<CORE::RapidJsonParser>();

        m_json_parser->parseJsonFile("sequence.json");

        TDS_LOG_INFO(m_json_parser->get("version"));

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

        // CORE::PluginManager::LoadPluginEvent.addListener([this](uint64_t pluginId, std::shared_ptr<CORE::PluginContainer> container)
        // {
        //     // 全局初始化
        //     if (container->isGlobal())
        //     {
        //         if (container->isEmpty())
        //         {
        //             container->create();
        //         }
        //         m_engineRunTest->addPlugin(pluginId, container->get(0));
        //     }
        // });

        CORE::PluginManager::OnDeserialize(m_json_parser);
        CORE::Engine::OnDeserialize(m_json_parser);

        m_json_parser->SerializeEvent.addListener([](CORE::RapidJsonParser::Writer& writer)
        {
            writer.StartObject();
            CORE::PluginManager::OnSerialize(writer);
            CORE::Engine::OnSerialize(writer);
            writer.EndObject();
        });
    }

    PanelSequenceEditor::~PanelSequenceEditor()
    {
        m_json_parser->saveJsonToFile("F:\\C_C++\\TardisProject\\Tardis\\build\\test\\Debug\\json_demo.json");
        CORE::PluginManager::DestroyAllPlugins();
    }

    void PanelSequenceEditor::drawImpl()
    {
        ImGui::Begin("Sequence Editor");
        const float TEXT_BASE_HEIGHT = ImGui::GetTextLineHeightWithSpacing();

        if(ImGui::Button(ICON_FA_PLAY, ImVec2(TEXT_BASE_HEIGHT + 16.0f, TEXT_BASE_HEIGHT + 16.0f)))
        {
            m_engineRunTest->runTask();
            //RunnerSelectedEvent.invoke()
           // CORE::Engine::runnerList.pop_back();
        }
        ImGui::SameLine();
        if(ImGui::Button(ICON_FA_TRASH, ImVec2(TEXT_BASE_HEIGHT + 16.0f, TEXT_BASE_HEIGHT + 16.0f)))
        {
            if(CORE::Engine::runnerList.size() > 0 )
            {
                CORE::Engine::runnerList.pop_back();
            }
        }
        ImGui::Button(ICON_FA_TRASH_ALT, ImVec2(TEXT_BASE_HEIGHT + 4.0f, TEXT_BASE_HEIGHT + 4.0f));ImGui::SameLine();
        ImGui::Button(ICON_FA_TRASH_RESTORE, ImVec2(TEXT_BASE_HEIGHT + 4.0f, TEXT_BASE_HEIGHT + 4.0f));ImGui::SameLine();
        ImGui::Button(ICON_FA_TRASH_RESTORE_ALT, ImVec2(TEXT_BASE_HEIGHT + 4.0f, TEXT_BASE_HEIGHT + 4.0f));ImGui::SameLine();
        ImGui::Button(ICON_FA_TREE, ImVec2(TEXT_BASE_HEIGHT + 4.0f, TEXT_BASE_HEIGHT + 4.0f));ImGui::SameLine();
        ImGui::Button(ICON_FA_TROPHY, ImVec2(TEXT_BASE_HEIGHT + 4.0f, TEXT_BASE_HEIGHT + 4.0f));ImGui::SameLine();
        ImGui::Button(ICON_FA_TRUCK, ImVec2(TEXT_BASE_HEIGHT + 4.0f, TEXT_BASE_HEIGHT + 4.0f));ImGui::SameLine();
        ImGui::Button(ICON_FA_TRUCK_LOADING, ImVec2(TEXT_BASE_HEIGHT + 4.0f, TEXT_BASE_HEIGHT + 4.0f));

        ImGui::Button(ICON_FA_TRUCK_MONSTER, ImVec2(TEXT_BASE_HEIGHT + 4.0f, TEXT_BASE_HEIGHT + 4.0f));ImGui::SameLine();
        ImGui::Button(ICON_FA_TRUCK_MOVING, ImVec2(TEXT_BASE_HEIGHT + 4.0f, TEXT_BASE_HEIGHT + 4.0f));ImGui::SameLine();
        ImGui::Button(ICON_FA_TRUCK_PICKUP, ImVec2(TEXT_BASE_HEIGHT + 4.0f, TEXT_BASE_HEIGHT + 4.0f));ImGui::SameLine();
        ImGui::Button(ICON_FA_TSHIRT, ImVec2(TEXT_BASE_HEIGHT + 4.0f, TEXT_BASE_HEIGHT + 4.0f));ImGui::SameLine();
        ImGui::Button(ICON_FA_TTY, ImVec2(TEXT_BASE_HEIGHT + 4.0f, TEXT_BASE_HEIGHT + 4.0f));ImGui::SameLine();
        ImGui::Button(ICON_FA_TV, ImVec2(TEXT_BASE_HEIGHT + 4.0f, TEXT_BASE_HEIGHT + 4.0f));

        ImGui::Button(ICON_FA_PLAY_CIRCLE, ImVec2(TEXT_BASE_HEIGHT + 4.0f, TEXT_BASE_HEIGHT + 4.0f));ImGui::SameLine();
        ImGui::Button(ICON_FA_PLUG, ImVec2(TEXT_BASE_HEIGHT + 4.0f, TEXT_BASE_HEIGHT + 4.0f));ImGui::SameLine();
        ImGui::Button(ICON_FA_PLUS, ImVec2(TEXT_BASE_HEIGHT + 4.0f, TEXT_BASE_HEIGHT + 4.0f));ImGui::SameLine();
        ImGui::Button(ICON_FA_PLUS_CIRCLE, ImVec2(TEXT_BASE_HEIGHT + 4.0f, TEXT_BASE_HEIGHT + 4.0f));ImGui::SameLine();
        ImGui::Button(ICON_FA_PLUS_SQUARE, ImVec2(TEXT_BASE_HEIGHT + 4.0f, TEXT_BASE_HEIGHT + 4.0f));ImGui::SameLine();
        ImGui::Button(ICON_FA_PODCAST, ImVec2(TEXT_BASE_HEIGHT + 4.0f, TEXT_BASE_HEIGHT + 4.0f));


        ImGui::BeginChild("3", ImVec2(0,0), false, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove);
        static bool isOpen = true;
        //if (ImGui::CollapsingHeader("Setup", &isOpen, ImGuiTreeNodeFlags_DefaultOpen))
        {
        
        //ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(4, 2) * 1.0f);
        static ImGuiTableFlags flagsSetup = ImGuiTableFlags_BordersV | /* ImGuiTableFlags_ScrollY | */ ImGuiTableFlags_Resizable |  ImGuiTableFlags_NoBordersInBody | ImGuiTableFlags_SizingFixedFit;
        if (ImGui::BeginTable("Sequences", 3,  flagsSetup))
        {
            ImGui::TableSetupScrollFreeze(0, 1);
            ImGui::TableSetupColumn("Status");
            ImGui::TableSetupColumn("Item");
            ImGui::TableSetupColumn("Test", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableHeadersRow();

           ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(6, 4) * 1.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(3, 0) * 1.0f);
            
            static int seleted_col = -1;
            int            dragIdx = -1;
            auto        &setupList = CORE::Engine::Setup;
            static ImVec2 lastItemMin(0.0f, 0.0f);
            static ImVec2 lastItemMax(0.0f, 0.0f);
            for (int test_n = 0; test_n < setupList.size(); test_n++)
            {
                ImGui::TableNextRow(ImGuiTableRowFlags_None);
                ImGui::PushID(("setup_" + std::to_string(test_n)).c_str());

                // Colors match general test status colors defined below.
                ImVec4 status_color;
                // status_color = ImVec4(0.8f, 0.0f, 0.8f, 1.0f);
                status_color = ImVec4(0.8f, 0.4f, 0.1f, 1.0f);

                ImGui::TableNextColumn();
                TestStatusButton("status", status_color, true);
                
                ImGui::SameLine();
                if(ImGui::SmallButton(ICON_FA_PLAY))
                {
                    TDS_LOG_INFO("runner{} is clicked.", test_n);
                    std::thread thread([this](int idx){ CORE::Engine::Setup[idx]->exec(m_engineSetup.get()); }, test_n);
		            thread.detach();
                }

                ImGui::TableNextColumn();
                
                if(ImGui::Selectable(setupList[test_n]->getName().c_str(), seleted_col == test_n, ImGuiSelectableFlags_AllowDoubleClick | ImGuiSelectableFlags_SpanAllColumns))
                {
                    if (ImGui::IsMouseDoubleClicked(0))
                    {
                        seleted_col = test_n;
                        RunnerSelectedEvent.invoke(setupList[test_n]);
                    }
                }

                auto min = ImGui::GetItemRectMin();
                auto max = ImGui::GetItemRectMax();
                if (test_n == setupList.size() - 1)
                {
                    lastItemMin = min;
                    lastItemMax = max;
                }
                if (ImGui::BeginDragDropTarget())
                {
                    dragIdx = test_n;
                    ImGuiDragDropFlags target_flags = 0;
                    target_flags |= ImGuiDragDropFlags_AcceptNoDrawDefaultRect;
                    ImGui::GetCurrentWindow()->DrawList->AddLine(min, ImVec2(max.x, min.y), IM_COL32(0, 255, 0, 255));

                    if (const ImGuiPayload *payload = ImGui::AcceptDragDropPayload("AddTestItem", target_flags))
                    {
                        std::shared_ptr<CORE::Runner> payload_n = *(std::shared_ptr<CORE::Runner>*)payload->Data;
                        setupList.insert(setupList.begin() + test_n, payload_n);
                    }
                    ImGui::EndDragDropTarget();
                }
                ImGui::TableNextColumn();
                ImGui::TextUnformatted("==");

                ImGui::PopID();
            }

          ImGui::Spacing();
            //ImGui::NewLine();
           ImGui::PopStyleVar(2);
            auto table = ImGui::GetCurrentTable();



            ImGui::EndTable();

            
            if (dragIdx == -1 && ImGui::BeginDragDropTarget())
            {
                ImGuiDragDropFlags target_flags = 0;
                target_flags |= ImGuiDragDropFlags_AcceptNoDrawDefaultRect;
                auto min = table->WorkRect.Min;
                auto max = table->WorkRect.Max;
               ImGui::GetForegroundDrawList()->AddLine(ImVec2(min.x, max.y - 3.0f), ImVec2(max.x, max.y - 3.0f), IM_COL32(0, 255, 0, 255));

                if (const ImGuiPayload *payload = ImGui::AcceptDragDropPayload("AddTestItem", target_flags))
                {
                    std::shared_ptr<CORE::Runner> payload_n = *(std::shared_ptr<CORE::Runner> *)payload->Data;
                    setupList.emplace_back(std::make_shared<CORE::Runner>(*payload_n.get()));
                }
                ImGui::EndDragDropTarget();
            }

        }
        }


        //const float   headerHeight = ImGui::GetFrameHeight();
        const float   headerHeight = ImGui::GetFrameHeightWithSpacing();
        static ImVec2 lastItemMin(0.0f, 0.0f);
        static ImVec2 lastItemMax(0.0f, 0.0f);
        int           dragIdx = -1;
        auto&         runnerList = CORE::Engine::runnerList;

        //ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, cell_padding);
        ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(4, 2) * 1.0f);
        static ImGuiTableFlags flagsSequence = ImGuiTableFlags_BordersV | /* ImGuiTableFlags_ScrollY | */ ImGuiTableFlags_Resizable |  ImGuiTableFlags_NoBordersInBody | ImGuiTableFlags_SizingFixedFit;

        if (ImGui::BeginTable("Sequences", 3,  flagsSequence))
        {
            ImGui::TableSetupScrollFreeze(0, 1);
            ImGui::TableSetupColumn("Status");
            ImGui::TableSetupColumn("Item");
            ImGui::TableSetupColumn("Test", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableHeadersRow();

            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(6, 4) * 1.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(3, 0) * 1.0f);
            
            static int seleted_col = -1;
            for (int test_n = 0; test_n < runnerList.size(); test_n++)
            {
                ImGui::TableNextRow(ImGuiTableRowFlags_None);
                ImGui::PushID(("runTask_" + std::to_string(test_n)).c_str());


                // Colors match general test status colors defined below.
                ImVec4 status_color;
                // status_color = ImVec4(0.8f, 0.0f, 0.8f, 1.0f);
                status_color = ImVec4(0.8f, 0.4f, 0.1f, 1.0f);

                ImGui::TableNextColumn();
                TestStatusButton("status", status_color, true);
                
                ImGui::SameLine();
                if(ImGui::SmallButton(ICON_FA_PLAY))
                {
                    TDS_LOG_INFO("runner{} is clicked.", test_n);
                    std::thread thread([this](int idx){ CORE::Engine::runnerList[idx]->exec(m_engineRunTest.get()); }, test_n);
		            thread.detach();
                }

                ImGui::TableNextColumn();
                
                if(ImGui::Selectable(runnerList[test_n]->getName().c_str(), 
                seleted_col == test_n, 
                ImGuiSelectableFlags_AllowDoubleClick | ImGuiSelectableFlags_SpanAllColumns))
                {
                    if (ImGui::IsMouseDoubleClicked(0))
                    {
                        seleted_col = test_n;
                        RunnerSelectedEvent.invoke(runnerList[test_n]);
                    }
                }

                auto min = ImGui::GetItemRectMin();
                auto max = ImGui::GetItemRectMax();
                if (test_n == runnerList.size() - 1)
                {
                    lastItemMin = min;
                    lastItemMax = max;
                }
                if (ImGui::BeginDragDropTarget())
                {
                    dragIdx = test_n;
                    ImGuiDragDropFlags target_flags = 0;
                    target_flags |= ImGuiDragDropFlags_AcceptNoDrawDefaultRect;
                    ImGui::GetCurrentWindow()->DrawList->AddLine(min, ImVec2(max.x, min.y), IM_COL32(0, 255, 0, 255));

                    if (const ImGuiPayload *payload = ImGui::AcceptDragDropPayload("AddTestItem", target_flags))
                    {
                        std::shared_ptr<CORE::Runner> payload_n = *(std::shared_ptr<CORE::Runner>*)payload->Data;
                        runnerList.insert(runnerList.begin() + test_n, payload_n);
                    }
                    ImGui::EndDragDropTarget();
                }
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
        if (runnerList.empty())
        {
            lastItemMin = ImGui::GetItemRectMin();
            lastItemMax = ImGui::GetItemRectMax();
            lastItemMax.y = lastItemMin.y + headerHeight;
        }

        if (dragIdx == -1 && ImGui::BeginDragDropTarget())
        {
            ImGuiDragDropFlags target_flags = 0;
            target_flags |= ImGuiDragDropFlags_AcceptNoDrawDefaultRect;

            ImGui::GetCurrentWindow()->DrawList->AddLine(ImVec2(lastItemMin.x, lastItemMax.y), lastItemMax, IM_COL32(0, 255, 0, 255));

            if (const ImGuiPayload *payload = ImGui::AcceptDragDropPayload("AddTestItem", target_flags))
            {
                std::shared_ptr<CORE::Runner> payload_n = *(std::shared_ptr<CORE::Runner> *)payload->Data;
                runnerList.emplace_back(std::make_shared<CORE::Runner>(*payload_n.get()));
            }
            ImGui::EndDragDropTarget();
        }
        ImGui::EndChild();

        ImGui::End();

    }
}