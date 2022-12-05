#include <memory>
//#include "OpenGLDevice.h"
#include "DirectX12Device.h"
#include "Application.h"
#include "WindowEditor.h"
//#include "WindowsManager.h"
//#include "PanelsManager.h"
//#include "DynamicModuleManager.h"

namespace TARDIS::UI
{
	Window* Application::m_currentWindow = nullptr;
	Application::Application()
	{
		m_renderDevice = std::make_unique<DirectX12Device>();
		m_renderDevice->initWindow();
		//m_currentWindow = WindowsManager::Create<CORE::WindowEditor>("Editor");
		m_currentWindow = new WindowEditor();
	}

	Application::~Application()
	{
        if (m_currentWindow)
        {
            delete m_currentWindow;
        }
        m_currentWindow = nullptr;

        // panels and windows should be released earlier.
		//PanelsManager::Destroy();
		//WindowsManager::Destroy();
	}

	void Application::run()
	{

		while (isRunning())
		{
			//m_renderDevice->preRender();

			m_currentWindow->update();

			m_renderDevice->render();
			//m_renderDevice->postRender();
		}
	}

	bool Application::isRunning()
	{
		return m_renderDevice->isRunning();
	}
}