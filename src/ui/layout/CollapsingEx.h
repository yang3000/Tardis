#pragma once

#include "../WidgetContainer.h"
#include "../AWidget.h"

#include "../imgui/imgui.h"
#include "../imgui/imgui_internal.h"

#include "Event.h"

namespace TARDIS::UI
{
	class CollapsingEx : public AWidget, public WidgetContainer
	{
	public:
		CollapsingEx(std::string header, bool isOpen = true, bool hasOp = true)
		: m_header(std::move(header))
		, m_isOpen(isOpen)
		, m_hasOp(hasOp)
		{};

        ~CollapsingEx()
        {
            printf("destroy CollapsingEx\r\n");
        }

		void updateHeader(std::string header)
		{
			m_header = std::move(header);
		}

		void setPopupFn(std::function<void(void)> fn) { m_popupFn = fn; }

		void setClosed() { m_isOpen = false; }

     public:
        CORE::Event<> CloseEvent;
        CORE::Event<> CloneEvent;

	protected:
		virtual void drawImpl() override;

	private:
		bool m_isOpen;
		bool m_hasOp;
		std::string m_header;

		ImVec2 m_regionMin;
		ImVec2 m_regionMax;

		std::function<void(void)> m_popupFn;
	};
}