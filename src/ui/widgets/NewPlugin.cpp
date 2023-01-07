#include "NewPlugin.h"

#include "../imgui/imgui.h"
//#include "../imgui/imgui_internal.h"

namespace TARDIS::UI
{
    void NewPlugin::drawImpl()
	{
        ImVec2 center = ImGui::GetMainViewport()->GetCenter();
        ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

       // auto& colors = ImGui::GetStyle().Colors;
       // auto windowBg = colors[ImGuiCol_PopupBg];
        //colors[ImGuiCol_PopupBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };

        if (ImGui::BeginPopupModal("New Plugin", NULL, ImGuiWindowFlags_AlwaysAutoResize))
        {
            static char name[128] = {0};
            static char path[128] = {0};
            ImGui::InputText("Name", name, sizeof(name));
            ImGui::InputText("Path", path, sizeof(path));
            ImGui::Separator();
            if (ImGui::Button("Create", ImVec2(120, 0)))
            {
                CreatePluginEvent.invoke(name, path);
                ImGui::CloseCurrentPopup();
            }
            ImGui::SetItemDefaultFocus();
            ImGui::SameLine();

            if (ImGui::Button("Cancel", ImVec2(120, 0)))
            {
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }
       //colors[ImGuiCol_PopupBg] = windowBg;
    }
}