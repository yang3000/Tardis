#pragma once

#include <memory>
#include "RenderDevice.h"
#include "Window.h"

namespace TARDIS::UI
{
	class Application
	{
	public:
		Application();
		~Application();
		void run();

	private:
		bool isRunning();

		static Window* m_currentWindow;

		std::unique_ptr<RenderDevice> m_renderDevice;
	};
}