#include "GroupChild.h"

#include "../imgui/imgui.h"
#include "../imgui/imgui_internal.h"


namespace TARDIS::UI
{
	void GroupChild::drawImpl()
	{
    //ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 8.0f));

    // ImGuiStyleVar_ItemInnerSpacing,    // ImVec2    ItemInnerSpacing
    // ImGuiStyleVar_IndentSpacing,       // float     IndentSpacing
    // ImGuiStyleVar_CellPadding,         // ImVec2    CellPadding

		ImGuiWindowFlags window_flags =  ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove;
		if(ImGui::BeginChild(m_widgetID.c_str(), ImVec2(0, 0), false, window_flags))
		{
			drawWidgets();
		ImGui::EndChild();
		}
		//ImGui::BeginChildFrame(ImGui::GetID(m_widgetID.c_str()), ImVec2(0, 0), window_flags);
		// drawWidgets();
		// ImGui::EndChild();
		//ImGui::EndChildFrame();
		//ImGui::PopStyleVar();

	}
}