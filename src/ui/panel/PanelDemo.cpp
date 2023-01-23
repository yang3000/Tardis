#include "PanelDemo.h"

#define IMGUI_DEFINE_MATH_OPERATORS
#include "../imgui/imgui.h"
#include "../imgui/imgui_internal.h"

#include "../layout/Collapsing.h"
#include "../layout/GroupChild.h"
#include "../widgets/DragScalarRange.h"

namespace TARDIS::UI
{
    PanelDemo::PanelDemo() : PanelWindow("PanelDemo")
    {
        createWidget<DragScalarRange>("S8", "3,4560", "100,1000", ImGuiDataType_S8);
        createWidget<DragScalarRange>("U8", "3,4560", "100,1000", ImGuiDataType_U8);

        createWidget<DragScalarRange>("S16", "300,4560", "100,1000", ImGuiDataType_S16);
        createWidget<DragScalarRange>("U16", "3,4560", "100,1000", ImGuiDataType_U16);

        createWidget<DragScalarRange>("S32", "3,4560", "100,1000", ImGuiDataType_S32);
        createWidget<DragScalarRange>("U32", "3,4560", "100,1000", ImGuiDataType_U32);

        createWidget<DragScalarRange>("S64", "3,4560", "100,1000", ImGuiDataType_S64);
        createWidget<DragScalarRange>("U64", "3,4560", "100,1000", ImGuiDataType_U64);
        createWidget<DragScalarRange>("Float", "123,456", "100,1000", ImGuiDataType_Float);
        createWidget<DragScalarRange>("Double", "123,456", "100,1000", ImGuiDataType_Double);
    }

    void PanelDemo::drawImpl()
    {
        static bool m_opened = true;
        ImGui::Begin((std::string("PanelDemo") + m_panelID).c_str(), &m_opened, 0);
        {
            drawWidgets();

            		float w_total = ImGui::CalcItemWidth();
		

            const float TEXT_BASE_WIDTH = ImGui::CalcTextSize("A").x;
			ImGui::PushItemWidth(w_total);
            if (ImGui::BeginTable("table1", 3, /* ImGuiTableFlags_BordersInnerV */ ImGuiTableFlags_NoBordersInBody, ImVec2(w_total, 0.0f)))
            {

                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0); ImGui::TextUnformatted("buf");
                ImGui::TableSetColumnIndex(1); ImGui::TextUnformatted("buf");
                ImGui::TableSetColumnIndex(2); ImGui::TextUnformatted("buf");

                ImGui::TableNextRow();
                char txt[128] ={0};
                ImGui::TableSetColumnIndex(0); ImGui::InputText("buf", txt, 128);
                ImGui::TableSetColumnIndex(1); ImGui::InputText("buf", txt, 128);
                ImGui::TableSetColumnIndex(2); ImGui::InputText("buf", txt, 128);

                ImGui::TableNextRow();
                char txt1[128] = "123";
                ImGui::TableSetColumnIndex(0); ImGui::InputText("", txt1, 128);
                ImGui::TableSetColumnIndex(1); ImGui::InputText("", txt1, 128);
                ImGui::TableSetColumnIndex(2); ImGui::InputText("", txt1, 128);

                ImGui::TableNextRow();
                bool t = true;
                ImGui::TableSetColumnIndex(0); ImGui::Checkbox("Skip",  &t);
                ImGui::TableSetColumnIndex(1); ImGui::Checkbox("Lock", &t);
                ImGui::TableSetColumnIndex(2); ImGui::Checkbox("Paused11111", &t);

                ImGui::TableNextRow();

                static float dummy_f = 0.0f;
                ImGui::TableSetColumnIndex(0); ImGui::SliderFloat("float0", &dummy_f, 0.0f, 1.0f);
                ImGui::TableSetColumnIndex(1); ImGui::SliderFloat("float1", &dummy_f, 0.0f, 1.0f);
                ImGui::TableSetColumnIndex(2); ImGui::SliderFloat("##float2", &dummy_f, 0.0f, 1.0f);

                ImGui::EndTable();
            }

            ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(2.0f, 2.0f));
           /// if (ImGui::BeginTable("table2", 2,ImGuiTableFlags_Borders, ImVec2(w_total, 0.0f)))
            if (ImGui::BeginTable("table2", 2,ImGuiTableFlags_BordersInnerV, ImVec2(w_total, 0.0f)))
            {

                ImGui::TableNextRow();
                char txt1[128] = "123";

                ImGui::TableSetColumnIndex(0);
                ImGui::PushItemWidth(-FLT_MIN); // Right-aligned
                ImGui::InputText("3e2", txt1, 128);
                ImGui::TableSetColumnIndex(1);
                //ImGui::PushItemWidth(-ImGui::GetContentRegionAvail().x * 0.5f);
                ImGui::PushItemWidth(-FLT_MIN); // Right-aligned
                ImGui::InputText("##1", txt1, 128);

                //ImGui::TableSetColumnIndex(0); ImGui::InputText("", txt1, 128);
                //ImGui::TableSetColumnIndex(1); ImGui::InputText("##1", txt1, 128);

                ImGui::TableNextRow();
                static float dummy_f = 0.0f;
                ImGui::TableSetColumnIndex(0); ImGui::SliderFloat("float0", &dummy_f, 0.0f, 1.0f);
                ImGui::TableSetColumnIndex(1); ImGui::SliderFloat("##float2", &dummy_f, 0.0f, 1.0f);

                ImGui::EndTable();
            }
            ImGui::PopStyleVar();


			ImGui::PopItemWidth();

        }
        ImGui::End();
    }
}