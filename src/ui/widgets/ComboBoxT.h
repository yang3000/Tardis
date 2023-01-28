#pragma once

#include "DataWidget.h"

#include <string>
#include <vector>

#include "Event.h"

namespace TARDIS::UI
{
	template <typename T>
	class ComboBoxT : public DataWidget<T>
	{
	public:
		ComboBoxT(const std::string &label, const T &currentChoice = 0)
			: DataWidget<T>(m_currentChoice)
			, m_currentChoice(currentChoice)
			, m_label(label)
		{}

		ComboBoxT& addElement(const T &value, const std::string &name)
		{
			m_choices.emplace(value, name);
			return *this;
		}

	protected:
		void drawImpl()
		{
			if (m_choices.size() == 0)
			{
				if (ImGui::BeginCombo((m_label + m_widgetID).c_str(), "Null"))
				{
					ImGui::EndCombo();
				}
				return;
			}

			if (m_choices.find(m_currentChoice) == m_choices.end())
			{
				m_currentChoice = m_choices.begin()->first;
			}
			
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
		}

	public:
		CORE::Event<T> ValueChangedEvent;

	private:
		T           m_currentChoice;
		std::string m_label;
		std::unordered_map<T, std::string> m_choices;
	};
}