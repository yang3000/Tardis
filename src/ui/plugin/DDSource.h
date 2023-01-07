#pragma once

#include "IPlugin.h"

#include "../imgui/imgui.h"

#include "Event.h"

namespace TARDIS::UI
{
    template<typename T>
    class DDSource : public IPlugin
    {
    public:

        DDSource(const std::string& identifier, const std::string& tooltip, T data) 
            : m_identifier(identifier)
            , m_tooltip(tooltip)
            , m_data(data)
            , m_isDragged(false)
        {}

        void execute() {
            ImGuiDragDropFlags src_flags = 0;
            src_flags |= ImGuiDragDropFlags_SourceNoDisableHover;
            src_flags |= ImGuiDragDropFlags_SourceNoHoldToOpenOthers;
            if (ImGui::BeginDragDropSource(src_flags))
            {
                if (!m_isDragged)
                {
                    DragStartEvent.invoke();
                }
                m_isDragged = true;

                ImGui::Text(m_tooltip.c_str());
                ImGui::SetDragDropPayload(m_identifier.c_str(), &m_data, sizeof(m_data));
                ImGui::EndDragDropSource();
            }
            else
            {
                if (m_isDragged)
                {
                    DragStopEvent.invoke();
                }
                m_isDragged = false;
            }
        }

    public:
        CORE::Event<> DragStartEvent;
        CORE::Event<> DragStopEvent;

    private:
        std::string m_identifier;
        std::string m_tooltip;
        T           m_data;
        bool        m_isDragged;
    };
}
