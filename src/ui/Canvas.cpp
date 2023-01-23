#include "Canvas.h"

#include <algorithm>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx12.h"

namespace TARDIS::UI
{
    void Canvas::draw()
    {
        // if (!m_panels.empty())
        {
            // Start the Dear ImGui frame
            ImGui_ImplDX12_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();

            // if (m_isDockspace)
            {
                static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

                // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
                // because it would be confusing to have two docking targets within each others.
                ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
                const ImGuiViewport *viewport = ImGui::GetMainViewport();
                ImGui::SetNextWindowPos(viewport->WorkPos);
                ImGui::SetNextWindowSize(viewport->WorkSize);
                ImGui::SetNextWindowViewport(viewport->ID);
                ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
                ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
               //ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.0f, 0.0f));
                ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));

                window_flags |= ImGuiWindowFlags_NoTitleBar;
                window_flags |= ImGuiWindowFlags_NoCollapse;
                window_flags |= ImGuiWindowFlags_NoResize;
                window_flags |= ImGuiWindowFlags_NoMove;
                window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
                window_flags |= ImGuiWindowFlags_NoNavFocus;

                // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
                // and handle the pass-thru hole, so we ask Begin() to not render a background.
                if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
                    window_flags |= ImGuiWindowFlags_NoBackground;

                // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
                // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
                // all active windows docked into it will lose their parent and become undocked.
                // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
                // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
                ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
                ImGui::Begin("##dockspace", nullptr, window_flags);
                ImGui::PopStyleVar(4);
                // ImGui::PopStyleVar(2);

                // ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8.0f, 8.0f));

                // Submit the DockSpace
                ImGuiIO &io = ImGui::GetIO();
                ImGuiStyle& style = ImGui::GetStyle();

                //float minWinSizeX = style.WindowMinSize.x;

                style.WindowMinSize.x = 320.0f;
               // style.IndentSpacing   = 0.0f;
                //style.FramePadding    = ImVec2(2.0f, 2.0f);
                style.ScrollbarSize     = 10.0f;
                style.ScrollbarRounding = 0.0f;
                style.WindowRounding = 4.0f;
                style.FrameRounding = 2.0f;
                style.GrabRounding = 2.0f;

                if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
                {
                    ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
                    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
                }
                auto& colors = ImGui::GetStyle().Colors;
                //colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };
                colors[ImGuiCol_PopupBg] = colors[ImGuiCol_WindowBg];
                colors[ImGuiCol_ScrollbarBg] = colors[ImGuiCol_WindowBg];
                colors[ImGuiCol_ScrollbarGrab] = colors[ImGuiCol_WindowBg];

                auto co = colors[ImGuiCol_ScrollbarGrabHovered];
                colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4{ co.x, co.y, co.z, 1.0f };
                colors[ImGuiCol_Header] = ImVec4{0.2f, 0.205f, 0.21f, 1.0f};
                colors[ImGuiCol_HeaderHovered] = ImVec4{0.2f, 0.205f, 0.21f, 1.0f};
                colors[ImGuiCol_HeaderActive] = ImVec4{0.2f, 0.205f, 0.21f, 1.0f};

                colors[ImGuiCol_Button] = ImVec4{0.2f, 0.205f, 0.21f, 1.0f};
                colors[ImGuiCol_ButtonHovered] = ImVec4{0.3f, 0.305f, 0.31f, 1.0f};
                colors[ImGuiCol_ButtonActive] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};

                colors[ImGuiCol_Tab] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
                colors[ImGuiCol_TabHovered] = ImVec4{0.38f, 0.3805f, 0.381f, 1.0f};
                colors[ImGuiCol_TabActive] = ImVec4{0.28f, 0.2805f, 0.281f, 1.0f};
                colors[ImGuiCol_TabUnfocused] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
                colors[ImGuiCol_TabUnfocusedActive] = ImVec4{0.2f, 0.205f, 0.21f, 1.0f};

                // Frame BG
                colors[ImGuiCol_FrameBg] = ImVec4{0.2f, 0.205f, 0.21f, 1.0f};
                colors[ImGuiCol_FrameBgHovered] = ImVec4{0.3f, 0.305f, 0.31f, 1.0f};
                colors[ImGuiCol_FrameBgActive] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};

                // Title
                colors[ImGuiCol_TitleBg] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
                colors[ImGuiCol_TitleBgActive] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
                colors[ImGuiCol_TitleBgCollapsed] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};

                //style.WindowMinSize.x = minWinSizeX;

                for (auto &panel : m_panels)
                {
                    panel.get().draw();
                }

                {
                    ImGui::Begin("Hello, world!"); // Create a window called "Hello, world!" and append into it.
                    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
                    ImGui::End();
                }

                ImGui::End();
            }

            ImGui::Render();
        }
    }

    void Canvas::addPanel(APanel &p_panel)
    {
        m_panels.push_back(std::ref(p_panel));
    }

    void Canvas::removePanel(APanel &p_panel)
    {
        m_panels.erase(std::remove_if(m_panels.begin(), m_panels.end(), [&p_panel](std::reference_wrapper<APanel> &p_item)
                                      { return &p_panel == &p_item.get(); }));
    }

    void Canvas::removeAllPanels()
    {
        m_panels.clear();
    }

    void Canvas::makeDockspace(bool p_state)
    {
        m_isDockspace = p_state;
    }

    bool Canvas::isDockspace() const
    {
        return m_isDockspace;
    }

}