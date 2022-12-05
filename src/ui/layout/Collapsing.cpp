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

		ImGui::PushID(m_widgetID.c_str());

        if (ImGui::CollapsingHeader(m_header.c_str(), &m_isOpen, ImGuiTreeNodeFlags_DefaultOpen))
        {
			drawWidgets();
        }

		ImGui::PopID();
	}
}