#include "CollapsingEx.h"


#include "IconsFontAwesome5.h"


namespace TARDIS::UI
{
	void CollapsingEx::drawImpl()
	{
		if (!m_isOpen)
		{
			destroy();
            CloseEvent.invoke();
		}

		ImGui::PushID(m_widgetID.c_str());

		//ImGui::BeginChild(m_widgetID.c_str());

			const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen |
													 ImGuiTreeNodeFlags_Framed |
													 ImGuiTreeNodeFlags_SpanAvailWidth |
													 ImGuiTreeNodeFlags_AllowItemOverlap |
													 ImGuiTreeNodeFlags_FramePadding;
			ImVec2 contentRegionAvailable = ImGui::GetContentRegionMax();
			// ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{4, 4});
			float lineHeight = ImGui::GetFrameHeight();
			// ImDrawList* draw_list = ImGui::GetWindowDrawList();
			// ImGui::PushClipRect(qq, qq1, true);
			// draw_list->AddRectFilled(qq, qq1, IM_COL32(90, 90, 120, 255));
			// ImGui::PopClipRect();

						m_regionMin = ImGui::GetCurrentContext()->LastItemData.Rect.Min;
			//m_regionMin.y += ImGui::GetFrameHeight();
			static bool open = false;
			if(open)
			{
				//ImGui::GetWindowDrawList()->AddRectFilled(m_regionMin, m_regionMax, IM_COL32(90, 90, 120, 255));
			}

			open = ImGui::TreeNodeEx("", treeNodeFlags, m_header.c_str());


			


			// ImGui::PopStyleVar();

			if (m_hasOp)
			{
				ImGui::SameLine(contentRegionAvailable.x - lineHeight);
				if (ImGui::Button(ICON_FA_PLUS, ImVec2{lineHeight, lineHeight}))
				{
					ImGui::OpenPopup("PopupMenu");
				}

				if (ImGui::BeginPopup("PopupMenu"))
				{
					// if (m_popupFn)
					// {
					// 	m_popupFn();
					// }
					if (ImGui::MenuItem("Clone"))
					{
						CloneEvent.invoke();
					}
					
					ImGui::EndPopup();
				}
			}

			if (open)
			{
				//ImGuiStyle& style = ImGui::GetStyle();
				//ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f });
				// ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 4.0f);
				// //ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, style.FrameBorderSize);
				// ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0,0));
				// bool ret = ImGui::BeginChild(ImGui::GetID(m_header.c_str()), ImVec2(0,0), false, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize);
				// ImGui::PopStyleVar(2);
				// ImGui::PopStyleColor();

				drawWidgets();
				//ImGui::PopStyleColor();
				// ImGui::EndChild();
				m_regionMax = ImGui::GetCurrentContext()->LastItemData.Rect.Max;
			    m_regionMax.y += ImGui::GetFrameHeight();
				ImGui::TreePop();
			}
		//ImGui::EndChild();

		ImGui::PopID();
	}
}