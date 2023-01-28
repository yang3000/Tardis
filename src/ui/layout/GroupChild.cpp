#include "GroupChild.h"

#include "../imgui/imgui.h"
#include "../imgui/imgui_internal.h"

namespace TARDIS::UI
{
	GroupChild::GroupChild(float padding_h, float padding_v)
		: m_padding_h(padding_h)
		, m_padding_v(padding_v)
	{}
	
	void GroupChild::drawImpl()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(m_padding_h, m_padding_v));
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysUseWindowPadding | ImGuiWindowFlags_AlwaysAutoResize;
		if (ImGui::BeginChild(m_widgetID.c_str(), ImVec2(0, 0), false, window_flags))
		{

			drawWidgets();
		}
		ImGui::EndChild();
		ImGui::PopStyleVar();
	}
}