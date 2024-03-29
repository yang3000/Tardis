#pragma once

#include "../AWidget.h"

#include <string>

namespace TARDIS::UI
{
	class Text : public AWidget
	{
	public:
		Text(const std::string& content = "");

	protected:
		void drawImpl() override;

	protected:
		std::string m_content;
	};
}
