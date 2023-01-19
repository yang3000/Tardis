#include "Group.h"

#include "../imgui/imgui.h"
#include "../imgui/imgui_internal.h"


namespace TARDIS::UI
{
	void Group::drawImpl()
	{
		ImGui::BeginGroup();
		drawWidgets();
		ImGui::EndGroup();
	}
}