#include "Collapsing.h"

#include "../imgui/imgui.h"


namespace TARDIS::UI
{
	void Collapsing::drawImpl()
	{
		if (!m_isOpen)
		{
			destroy();
            CloseEvent.invoke();
		}

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8.0f, 8.0f));
        if (ImGui::CollapsingHeader((m_header + m_widgetID).c_str(), &m_isOpen, ImGuiTreeNodeFlags_DefaultOpen))
        {
			drawWidgets();
        }
		ImGui::PopStyleVar();
	}
}