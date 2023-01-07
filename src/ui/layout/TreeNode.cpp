#include "TreeNode.h"

#include "../imgui/imgui.h"


namespace TARDIS::UI
{
	void TreeNode::drawImpl()
	{
		ImGui::PushID(m_widgetID.c_str());
		if (ImGui::TreeNode(m_header.c_str()))
        {
            drawWidgets();
			ImGui::TreePop();
        }
		ImGui::PopID();
	}
}