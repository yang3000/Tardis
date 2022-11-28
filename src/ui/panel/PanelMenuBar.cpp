#include "PanelMenuBar.h"

#include "../imgui/imgui.h"


namespace TARDIS::UI
{
    void PanelMenuBar::drawImpl()
    {
        // if (!m_widgets.empty() && ImGui::BeginMainMenuBar())
        // {
        //     DrawWidgets();
        //     ImGui::EndMainMenuBar();
        // }
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.0f, 8.0f));
        if (ImGui::BeginMainMenuBar())
        {
                        ImGui::Button("Tardis", ImVec2(32, 32));
            ImGui::SameLine();
            if (ImGui::BeginMenu("Edit"))
            {
                if (ImGui::MenuItem("Undo", "CTRL+Z"))
                {
                }
                if (ImGui::MenuItem("Redo", "CTRL+Y", false, false))
                {
                } // Disabled item
                ImGui::Separator();
                if (ImGui::MenuItem("Cut", "CTRL+X"))
                {
                }
                if (ImGui::MenuItem("Copy", "CTRL+C"))
                {
                }
                if (ImGui::MenuItem("Paste", "CTRL+V"))
                { }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Demo"))
            {
                if (ImGui::MenuItem("Undo", "CTRL+Z"))
                {
                }
                if (ImGui::MenuItem("Redo", "CTRL+Y", false, false))
                {
                } // Disabled item
                ImGui::Separator();
                if (ImGui::MenuItem("Cut", "CTRL+X"))
                {
                }
                if (ImGui::MenuItem("Copy", "CTRL+C"))
                {
                }
                if (ImGui::MenuItem("Paste", "CTRL+V"))
                { }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
        ImGui::PopStyleVar();


        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.0f, 16.0f));
        if (ImGui::BeginMenuBar())
        {
            ImGui::Button("Tardis", ImVec2(64, 64));
            ImGui::SameLine();
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
        ImGui::PopStyleVar();
    }
}