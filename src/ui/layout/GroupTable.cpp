#include "GroupTable.h"

#include "../imgui/imgui.h"
#include "../imgui/imgui_internal.h"


namespace TARDIS::UI
{
	GroupTable::GroupTable(unsigned int columns)
		: m_columns(columns)
	{}

	void GroupTable::drawImpl()
	{
		ImGui::Columns(m_columns, NULL, true);

		for (int i = 0; i < m_widgets.size(); i++)
        {
            // if (ImGui::GetColumnIndex() == 0)
			// {
            //     ImGui::Separator();
			// }
			drawWidgets();
            // ImGui::Text("Long text that is likely to clip");
            // ImGui::Button("Button", ImVec2(-FLT_MIN, 0.0f));
			ImGui::Separator();
            ImGui::NextColumn();
        }

        ImGui::Columns(1);
	}
}