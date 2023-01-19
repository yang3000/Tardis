#include "PopupWindow.h"

#include "../imgui/imgui.h"
#include "../imgui/imgui_internal.h"


namespace TARDIS::UI
{
	PopupWindow::PopupWindow(const std::string &popupId)
		: m_popupId(popupId)
	{}

	void PopupWindow::drawImpl()
	{
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(4.0f, 4.0f));
		if (ImGui::BeginPopup((m_popupId + m_widgetID).c_str()))
		{
			drawWidgets();
			ImGui::EndPopup();
		}
		ImGui::PopStyleVar();
	}
}