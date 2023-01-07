#pragma once

#include "AButton.h"

#include <string>

#include "../imgui/imgui.h"


namespace TARDIS::UI
{
	class Button : public AButton
	{
	public:
		Button(const std::string& label,  const ImVec2& size = ImVec2(0, 0));

		void disabled(bool disabled = true);

	protected:
		void drawImpl() override;

	private:
		std::string  m_label;
		ImVec2       m_size;
		bool         m_disabled;
	};
}
