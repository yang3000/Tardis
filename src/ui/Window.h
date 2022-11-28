#pragma once

#include <memory>
#include "panel/APanel.h"
#include "Canvas.h"


namespace TARDIS::UI
{
	class Window
	{
	public:
        Window()
        {
            m_canvas = std::make_unique<Canvas>();
        };

        virtual ~Window() {}

		void update()
		{
			updateImpl();
			m_canvas->draw();
		}

		void addPanel(APanel& p_panel)
		{
			m_canvas->addPanel(p_panel);
		}

	private:
		virtual void updateImpl() = 0;

		std::unique_ptr<Canvas> m_canvas;
	};
}