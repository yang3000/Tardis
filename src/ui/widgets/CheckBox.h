#pragma once

#include "DataWidget.h"

#include <string>

#include "Event.h"

namespace TARDIS::UI
{
	class CheckBox : public DataWidget<bool>
	{
	public:
		CheckBox(const std::string& label = "", bool value = false);

		void sameline() {}

	protected:
		void drawImpl() override;

    public:
        CORE::Event<bool> ValueChangedEvent;
	protected:
		bool        m_value;
		std::string m_label;
	};
}
