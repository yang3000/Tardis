#include "LabelText.h"

#include "../imgui/imgui.h"

namespace TARDIS::UI
{
    LabelText::LabelText(const std::string& label, const std::string &content)
        : m_label(label)
        , m_content(content)
    {}

    void LabelText::drawImpl()
    {
        ImGui::LabelText(m_label.c_str(), m_content.c_str());
    }
}