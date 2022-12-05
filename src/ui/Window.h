#pragma once

#include <memory>
#include "panel/APanel.h"
#include "Canvas.h"
#include "PanelsManager.h"


namespace TARDIS::UI
{
	class Window
	{
	public:
        Window() : m_panelsManager(m_canvas)
        { };

        virtual ~Window() {}

		void update()
		{
			// updateImpl();
			m_canvas.draw();
		}

	private:
		//virtual void updateImpl() = 0;
        Canvas        m_canvas;

    protected:
        PanelsManager m_panelsManager;
	};
}