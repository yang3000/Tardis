#pragma once

#include "DataWidget.h"

#include <string>

#include "Event.h"

namespace TARDIS::UI
{
	class InputText : public DataWidget<std::string>
	{
	public:
		InputText(const std::string& label, const std::string& content = "");

		const std::string GetLabel() const { return m_label; };
		const std::string GetContent() const { return m_content; };

	protected:
		void drawImpl() override;

    public:
        CORE::Event<std::string> TextChangedEvent;
        CORE::Event<std::string> EnterPressedEvent;

	private:
		std::string m_label;
		std::string m_content;
	};
}
