#pragma once

#include "AWidget.h"

#include <string>

namespace TARDIS::UI
{
	class LabelText : public AWidget
	{
	public:
		LabelText(const std::string& label = "", const std::string& content = "");

	protected:
		void drawImpl() override;

	protected:
		std::string m_label;
		std::string m_content;
	};
}
