#include "TestItemList.h"

#define IMGUI_DEFINE_MATH_OPERATORS
#include "../imgui/imgui.h"
#include "../imgui/imgui_internal.h"

namespace TARDIS::UI
{
    void TestItemList::drawImpl()
    {
        ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(4, 2) * 1.0f);
        static ImGuiTableFlags flagsSequence = ImGuiTableFlags_BordersV | ImGuiTableFlags_ScrollY | ImGuiTableFlags_Resizable |  ImGuiTableFlags_NoBordersInBody | ImGuiTableFlags_SizingFixedFit;

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
            
            // static int seleted_col = -1;
            // for (int i = 0; i < m_testItemList.size(); ++i)
            // {
            //     ImGui::TableNextRow(ImGuiTableRowFlags_None);
            //     ImGui::PushID(("test_stand_" + std::to_string(i)).c_str());

            //     ImVec4 status_color  = ImVec4(0.8f, 0.4f, 0.1f, 1.0f);

            //     ImGui::TableNextColumn();
            //     ImGui::Selectable(std::to_string(i + 1).c_str(), false, ImGuiSelectableFlags_SpanAllColumns);

            //     ImGui::TableNextColumn();
            //     ImGui::Text(m_testItemList[i]->name.c_str());

            //     ImGui::TableNextColumn();
            //     ImGui::Text(m_testItemList[i]->desc.c_str());

            //     ImGui::TableNextColumn();
            //     ImGui::Text(m_testItemList[i]->lower.c_str());

            //     ImGui::TableNextColumn();
            //     ImGui::Text(m_testItemList[i]->value.c_str());

            //     ImGui::TableNextColumn();
            //     ImGui::Text(m_testItemList[i]->upper.c_str());
              
            //     ImGui::TableNextColumn();
            //     ImGui::TextUnformatted("==");

            //     ImGui::PopID();
            // }

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

    }
}