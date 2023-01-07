#pragma once

#include "../WidgetContainer.h"
#include "../AWidget.h"

namespace TARDIS::UI
{
	class TreeNode : public AWidget, public WidgetContainer
	{
	public:
		TreeNode(std::string header) 
			: m_header(std::move(header))
		{};

        ~TreeNode()
        {
            printf("destroy TreeNode\r\n");
        }

	protected:
		virtual void drawImpl() override;

	private:
		std::string m_header;
	};
}