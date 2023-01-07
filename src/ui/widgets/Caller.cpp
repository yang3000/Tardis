#include "Caller.h"

#include "../imgui/imgui.h"
#include "../imgui/imgui_internal.h"

namespace TARDIS::UI
{
    void Caller::drawImpl()
	{
        // ImGuiStyle& style = ImGui::GetStyle();
        // float indentSpacingOld = style.IndentSpacing;
        // style.IndentSpacing = 0.0f;

        //ImGui::Selectable(m_content.c_str(), &m_selected);
        //bool selected = false;
        ImGui::Selectable(m_content.c_str(), &m_selected); 
        //ImGui::Text("2,345 bytes");
        //style.IndentSpacing = indentSpacingOld;
	}
}