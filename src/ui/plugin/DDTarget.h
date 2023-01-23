#pragma once

#include "IPlugin.h"

#include "../imgui/imgui.h"

#include "Event.h"

namespace TARDIS::UI
{
    template<typename T>
    class DDTarget : public IPlugin
    {
    public:
        DDTarget(const std::string& identifier) 
            : m_identifier(identifier)
            , m_isHovered(false)
        {}

        void execute()
        {
            if (ImGui::BeginDragDropTarget())
			{
				if (!m_isHovered)
                {
					HoverStartEvent.invoke();
                }
				m_isHovered = true;

				ImGuiDragDropFlags target_flags = 0;
				//target_flags |= ImGuiDragDropFlags_AcceptNoDrawDefaultRect;

                auto min = ImGui::GetItemRectMin();
                auto max = ImGui::GetItemRectMax();
                ImGui::GetCurrentWindow()->DrawList->AddLine(ImVec2(min.x, max.y), max, IM_COL32(0, 255, 0, 255));

                if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(m_identifier.c_str(), target_flags))
				{
					T data = *(T*)payload->Data;
					DataReceivedEvent.invoke(data);
				}
				ImGui::EndDragDropTarget();
			}
			else
			{
				if (m_isHovered)
                {
                    HoverEndEvent.invoke();
                }
				m_isHovered = false;
			}
        }

    public:
        CORE::Event<T> DataReceivedEvent;
        CORE::Event<>  DragStartEvent;
        CORE::Event<>  DragStopEvent;

    private:
        std::string m_identifier;
        bool        m_isHovered;
    };
}
