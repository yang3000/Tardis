#pragma once

#include "Window.h"
//#include "Canvas.h"

//#include "MenuBar.h"

namespace TARDIS::UI
{
	class WindowEditor : public Window
	{
	public:
		WindowEditor();
		~WindowEditor();

		void setup();

		void updateImpl() override;

		void handleCloseEvent();

	private:
		void setDockSpaceBegin();

		void setDockSpaceEnd();

		void setupMenuBar();

		bool show_demo = false;
	};
}