#pragma once

#include "../WidgetContainer.h"
#include "../AWidget.h"
#include "Event.h"

namespace TARDIS::UI
{
	class Collapsing : public AWidget, public WidgetContainer
	{
	public:
		Collapsing(std::string header) : 
			m_header(std::move(header)),
			m_isOpen(true)
		{};

        ~Collapsing()
        {
            printf("destroy Collapsing\r\n");
        }

		void updateHeader(std::string header)
		{
			m_header = std::move(header);
		}

     public:
        CORE::Event<> CloseEvent;

	protected:
		virtual void drawImpl() override;

	private:
		bool m_isOpen;
		std::string m_header;
	};
}