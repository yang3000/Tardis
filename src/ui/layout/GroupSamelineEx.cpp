#include "GroupSamelineEx.h"

#include "../imgui/imgui.h"
#include "../imgui/imgui_internal.h"
#include <memory>

namespace TARDIS::UI
{
	GroupSamelineEx::GroupSamelineEx(const std::string& label, bool autoColumnWidth)
		: m_label(label)
		, m_autoColumnWidth(autoColumnWidth)
	{}

	void GroupSamelineEx::drawImpl()
	{
		collectGarbages();
		auto count = m_widgets.size();
		auto width = ImGui::CalcItemWidth();
		ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(2.0f, 0.0f));
		ImGui::PushItemWidth(width);

		if (ImGui::BeginTable(
			(std::string("GroupSamelineEx") + m_widgetID).c_str(), 
			count, 
			0, 
			ImVec2(width, 0.0f)))
		{
			if (!m_autoColumnWidth)
			{
				for (int i = 0; i < count; ++i)
				{
					auto columnWidth = m_widgets[i]->getWidth() <= 0.0f ? 0.0f : m_widgets[i]->getWidth() * width;
					ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, columnWidth);
				}
			}

			ImGui::TableNextRow();
			for (int i = 0; i < count; ++i)
			{
				ImGui::TableSetColumnIndex(i);
				ImGui::PushItemWidth(-FLT_MIN);
				m_widgets[i]->draw();
			}
			ImGui::EndTable();
		}
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();
		
		if(m_label.size())
		{
			ImGui::SameLine(0.0f, 4.0f);
			ImGui::Text(m_label.c_str());
		}
	}
}