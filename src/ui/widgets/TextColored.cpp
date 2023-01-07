#include "TextColored.h"

#include "../imgui/imgui.h"

namespace TARDIS::UI
{
    TextColored::TextColored(const std::string &content, const ImVec4& col)
        : Text(content)
        , m_color(col)
    {}

    void TextColored::drawImpl()
    {
        ImGui::TextColored(m_color, m_content.c_str());
    }
}