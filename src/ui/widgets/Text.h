#pragma once

#include "DataWidget.h"

#include <string>

namespace TARDIS::UI
{
	class Text : public DataWidget<std::string>
	{
	public:
		Text(const std::string& content = "");

	protected:
		void drawImpl() override;

	protected:
		std::string m_content;
	};
}
