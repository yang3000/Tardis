#include "PanelSequenceEditor.h"

#define IMGUI_DEFINE_MATH_OPERATORS
#include "../imgui/imgui.h"
#include "../imgui/imgui_internal.h"

#include "Engine.h"
#include "RapidJsonParser.h"

namespace TARDIS::UI
{
    void PanelSequenceEditor::TestStatusButton(const char *id, const ImVec4 &color, bool running)
    {
        ImGuiContext &g = *GImGui;
        ImGui::ColorButton(id, color, ImGuiColorEditFlags_NoTooltip);
        if (running)
        {
            // ImRect r = g.LastItemData.Rect;
            ImVec2 center = g.LastItemData.Rect.GetCenter();
            float radius = ImFloor(ImMin(g.LastItemData.Rect.GetWidth(), g.LastItemData.Rect.GetHeight()) * 0.40f);
            float t = (float)(ImGui::GetTime() * 10.0f);
            ImVec2 off(ImCos(t) * radius, ImSin(t) * radius);
            ImGui::GetWindowDrawList()->AddLine(center - off, center + off, ImGui::GetColorU32(ImGuiCol_Text), 1.5f);
            // ImGui::RenderText(r.Min + style.FramePadding + ImVec2(0, 0), &"|\0/\0-\0\\"[(((ImGui::GetFrameCount() / 5) & 3) << 1)], NULL);
        }
    }

    PanelSequenceEditor::PanelSequenceEditor()
    {
        auto jsonParser = std::make_shared<CORE::RapidJsonParser>();
        jsonParser->parseJsonFile("sequence.json");

        TDS_LOG_INFO(jsonParser->get("version"));

        if (jsonParser->nodeBegin("sequences"))
        {
            CORE::Engine::OnDeserialize(jsonParser);
            jsonParser->nodeEnd();
        }

    }

    void PanelSequenceEditor::drawImpl()
    {
        ImGui::Begin("Sequence Editor");
        
        if (ImGui::BeginTable("Sequences", 3, ImGuiTableFlags_ScrollY | ImGuiTableFlags_Resizable | ImGuiTableFlags_NoBordersInBody | ImGuiTableFlags_SizingFixedFit))
        {
            ImGui::TableSetupScrollFreeze(0, 1);
            ImGui::TableSetupColumn("Status");
            ImGui::TableSetupColumn("Group");
            ImGui::TableSetupColumn("Test", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableHeadersRow();

            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(6, 4) * 1.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4, 0) * 1.0f);
            // ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(100, 10) * dpi_scale);
            static int seleted_col = -1;
            
            auto runnerList = CORE::Engine::runnerList;
            for (int test_n = 0; test_n < runnerList.size(); test_n++)
            {
                ImGui::TableNextRow();
                ImGui::PushID(test_n);

                // Colors match general test status colors defined below.
                ImVec4 status_color;
                // status_color = ImVec4(0.8f, 0.0f, 0.8f, 1.0f);
                status_color = ImVec4(0.8f, 0.4f, 0.1f, 1.0f);

                ImGui::TableNextColumn();
                TestStatusButton("status", status_color, true);
                ImGui::SameLine();

                bool queue_test = false;
                bool queue_gui_func_toggle = false;
                bool select_test = false;

                //ImGui::Button("Run###Run");

                ImGui::TableNextColumn();
                
                if(ImGui::Selectable(runnerList[test_n]->getName().c_str(), seleted_col == test_n, ImGuiSelectableFlags_SpanAllColumns | ImGuiSelectableFlags_SelectOnNav))
                {
                    seleted_col = test_n;
                }

                //if (e->UiSelectAndScrollToTest == test)
                    //ImGui::SetScrollHereY();

             

                ImGui::TableNextColumn();
                ImGui::TextUnformatted("43543534543");

                ImGui::PopID();
            }
            ImGui::Spacing();
            ImGui::PopStyleVar(2);
            ImGui::EndTable();
        }
        ImGui::End();

    }
}