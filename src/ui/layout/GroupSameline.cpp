#include "GroupSameline.h"

#include "../imgui/imgui.h"
#include "../imgui/imgui_internal.h"


namespace TARDIS::UI
{
	void GroupSameline::drawImpl()
	{
		collectGarbages();
 
		auto count = m_widgets.size();

		ImGuiStyle& style = ImGui::GetStyle();

		float w_sum  = 0.0f;
		float w_total = ImGui::CalcItemWidth() - (style.ItemSpacing.x) * (count -1);
		

		for(int i = 0; i < count; ++i)
		{
			const float w_item  = IM_FLOOR(w_total * m_widgets[i]->width);
			ImGui::PushItemWidth(i < count - 1 ? w_item : w_total - w_sum);
			m_widgets[i]->draw();
			ImGui::PopItemWidth();
			if(i < count - 1)
			{
				ImGui::SameLine();
			}
			w_sum += w_item;// + style.ItemSpacing.x;
		}
	}
}