#include "PanelMenuBar.h"

#include "../imgui/imgui.h"


namespace TARDIS::UI
{
    void PanelMenuBar::drawImpl()
    {
        //ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.0f, 16.0f));
        if (ImGui::BeginMenuBar())
        {
            // ImGui::Button(ICON_FA_DNA, ImVec2(32, 32)); ImGui::SameLine();
            if (ImGui::BeginMenu("Examples"))
            {
                ImGui::MenuItem("Fullscreen", NULL);
                ImGui::MenuItem("Padding", NULL);
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Demo"))
            {
                ImGui::MenuItem("Fullscreen", NULL);
                ImGui::MenuItem("Padding", NULL);
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }
       // ImGui::PopStyleVar();
    }
}