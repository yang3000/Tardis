#include "CheckBox.h"

#include "../imgui/imgui.h"

namespace TARDIS::UI
{
    CheckBox::CheckBox(const std::string& label, bool value)
        : DataWidget<bool>(m_value)
        , m_value(value)
        , m_label(label)
    {}

    void CheckBox::drawImpl()
    {

        auto itemWidth = ImGui::CalcItemWidth();

       // ImGui::PushItemWidth(itemWidth * width);
        bool previousValue = m_value;
        ImGui::Checkbox((m_label + m_widgetID).c_str(), &m_value);
		//ImGui::PopItemWidth();

        if (m_value != previousValue)
        {
            ValueChangedEvent.invoke(m_value);
            this->notifyChange();
        }
    }
}