#include "PopupWindow.h"

#include "../imgui/imgui.h"
#include "../imgui/imgui_internal.h"


namespace TARDIS::UI
{
	void PopupWindow::drawImpl()
	{
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove;
		if (ImGui::BeginChild(m_widgetID.c_str(), ImVec2(0, 0), false, window_flags))
		{
			drawWidgets();
			ImGui::EndChild();
		}
	}
}