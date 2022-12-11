#include "HelperMarker.h"

#include "../imgui/imgui.h"

namespace TARDIS::UI
{
    HelperMarker::HelperMarker(std::string marker, bool isSameline)
        : m_marker(marker)
        , m_sameline(isSameline)
    {};

    void HelperMarker::drawImpl()
    {
        ImGui::TextDisabled("(?)");
        if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort))
        {
            ImGui::BeginTooltip();
            ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
            ImGui::TextUnformatted(m_marker.c_str());
            ImGui::PopTextWrapPos();
            ImGui::EndTooltip();
        }
        if (m_sameline)
        {
            ImGui::SameLine();
        }
    }
}