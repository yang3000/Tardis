#pragma once

#include "../WidgetContainer.h"
#include "../AWidget.h"

#include "../imgui/imgui.h"
#include "../imgui/imgui_internal.h"

#include "Event.h"
#include "./PopupWindow.h"
#include <memory>


namespace TARDIS::UI
{
	class CollapsingEx : public AWidget, public WidgetContainer
	{
	public:
		CollapsingEx(std::string header, bool isOpen = true, bool hasOp = true)
		: m_header(std::move(header))
		, m_isOpen(isOpen)
		, m_hasOp(hasOp)
		, m_popupWin(std::make_shared<PopupWindow>("CollapsingPopuoMenu"))
		{};

        ~CollapsingEx()
        {
            printf("destroy CollapsingEx\r\n");
        }

		void updateHeader(std::string header)
		{
			m_header = std::move(header);
		}

		template <typename T, typename ... Args>
		T& addPopupMenu(Args&&... p_args)
		{
			return m_popupWin->createWidget<T>(std::forward<Args>(p_args)...);
		}

		void setClosed() { m_isOpen = false; }

     public:
        CORE::Event<> CloseEvent;

	protected:
		virtual void drawImpl() override;

	private:
		bool m_isOpen;
		bool m_hasOp;
		std::string m_header;

		ImVec2 m_regionMin;
		ImVec2 m_regionMax;

		std::shared_ptr<PopupWindow> m_popupWin;
	};
}