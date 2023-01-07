#pragma once

#include "Text.h"

#include <string>

#include "../imgui/imgui.h"

namespace TARDIS::UI
{
	class TextColored : public Text
	{
	public:
		TextColored(const std::string& content = "", const ImVec4& col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f));

	protected:
		void drawImpl() override;

	private:
		ImVec4 m_color;
	};
}
