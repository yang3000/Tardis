#include "InputText.h"

#include "../imgui/imgui.h"
//#include "../imgui/imgui_internal.h"

//#include "EventArgs.h"

namespace TARDIS::UI
{
    InputText::InputText(const std::string &label, const std::string &content)
        : DataWidget<std::string>(m_content)
        , m_label(label)
        , m_content(content)
    {}

    void InputText::drawImpl()
    {
        Char content[256] = {0};
        memcpy_s(content, sizeof(content), m_content.c_str(), m_content.size());

        bool enterPressed = ImGui::InputText((m_label + m_widgetID).c_str(), content, sizeof(content), ImGuiInputTextFlags_EnterReturnsTrue);
        if ( content[m_content.size()] != 0 || memcmp(m_content.c_str(), content, m_content.size()) != 0)
        {
            m_content = content;
            this->notifyChange();
            TextChangedEvent.invoke(m_content);
        }

        if (enterPressed)
        {
            EnterPressedEvent.invoke(m_content);
        }
    }
}