#pragma once

#include "DataWidget.h"

#include <string>
#include <vector>

#include "Event.h"

namespace TARDIS::UI
{
	class ComboBox : public DataWidget<uint64_t>
	{
	public:
		ComboBox(const std::string& label, const uint64_t& currentChoice = 0);

		void addElement(const uint64_t& value, const std::string& name);

	protected:
		void drawImpl() override;

    public:
        CORE::Event<uint64_t> ValueChangedEvent;

	private:
		std::unordered_map<uint64_t, std::string> m_choices;
		std::string m_label;
		uint64_t    m_currentChoice;
	};
}