#include "Text.h"

#include "../imgui/imgui.h"

namespace TARDIS::UI
{
    Text::Text(const std::string &content)
        : m_content(content)
    {}

    void Text::drawImpl()
    {
        ImGui::Text(m_content.c_str());
    }
}