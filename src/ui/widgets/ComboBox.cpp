#include "ComboBox.h"

#include "../imgui/imgui.h"

namespace TARDIS::UI
{
    ComboBox::ComboBox(const std::string& label, const uint64_t& currentChoice)
        : DataWidget<uint64_t>(m_currentChoice)
        , m_label(label)
        , m_currentChoice(currentChoice)
    {}

    void ComboBox::addElement(const uint64_t& value, const std::string& name)
    {
        m_choices.emplace(value, name);
    }

    void ComboBox::drawImpl()
    {
        if(m_choices.size() == 0)
        {
	        //ImGui::PushItemWidth(ImGui::CalcItemWidth() * width);

            if(ImGui::BeginCombo((m_label + m_widgetID).c_str(), ""))
            {
                ImGui::EndCombo();
            }
		    //ImGui::PopItemWidth();

            return;

        }

        if (m_choices.find(m_currentChoice) == m_choices.end())
        {
            m_currentChoice = m_choices.begin()->first;
        }
	        //ImGui::PushItemWidth(ImGui::CalcItemWidth() * width);

        if (ImGui::BeginCombo((m_label + m_widgetID).c_str(), m_choices[m_currentChoice].c_str()))
        {
            for (const auto &[value, name] : m_choices)
            {
                bool selected = value == m_currentChoice;
                if (ImGui::Selectable(name.c_str(), selected))
                {
                    if (!selected)
                    {
                        ImGui::SetItemDefaultFocus();
                        m_currentChoice = value;
                        this->notifyChange();
                        ValueChangedEvent.invoke(m_currentChoice);
                    }
                }
            }

            ImGui::EndCombo();
        }
        //ImGui::PopItemWidth();
    }
}