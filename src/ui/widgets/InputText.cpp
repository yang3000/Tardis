#include "InputText.h"

#include "../imgui/imgui.h"
//#include "../imgui/imgui_internal.h"

//#include "EventArgs.h"

namespace TARDIS::UI
{
	InputText::InputText(const std::string& label, const std::string& content) :
		DataWidget<std::string>(m_content),
		m_label(label),
		m_content(content)
	{}

	void InputText::drawImpl()
	{
		std::string preContent{m_content};
		m_content.resize(256, '\0');
		bool enterPressed = ImGui::InputText((m_label + m_widgetID).c_str(), &m_content[0], 256, ImGuiInputTextFlags_EnterReturnsTrue);
		m_content = m_content.c_str();

		if (m_content != preContent)
		{
			this->notifyChange();
            TextChangedEvent.invoke(m_content);
		}

		if (enterPressed)
		{
            EnterPressedEvent.invoke(m_content);
		}
	}
}