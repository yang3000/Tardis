#pragma once

#include "Button.h"

#include <string>

#include "../imgui/imgui_internal.h"

namespace TARDIS::UI
{
    Button::Button(const std::string &label, const ImVec2& size) 
        : m_label(label)
        , m_size(size)
        , m_disabled(false)
    {}

    void Button::disabled(bool disabled)
    {
        m_disabled = disabled;
    }

    void Button::drawImpl()
    {
        if(m_disabled)
        {
            ImGui::BeginDisabled();
        }
        if (ImGui::ButtonEx((m_label + m_widgetID).c_str(), m_size, ImGuiButtonFlags_None))
        {
		    ClickedEvent.invoke();
        }
        if(m_disabled)
        {
            ImGui::EndDisabled();
        }
    }
}
