#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"

#include "WindowTestStand.h"
#include "panel/PanelMenuBar.h"
#include "panel/PanelTestStand.h"
#include "panel/PanelProperties.h"
#include "panel/PanelPluginManager.h"
#include "PanelsManager.h"
#include "IconsFontAwesome5.h"
#include "Runner.h"
//#include "EngineManager.h"
#include "PluginManager.h"
//#include "RapidJsonParser.h"
//#include "RunnerProperty.h"


namespace TARDIS::UI
{
	WindowTestStand::WindowTestStand()
	{
		setup();
	}
	WindowTestStand::~WindowTestStand()
	{
	}


	void WindowTestStand::setup()
	{
        m_panelsManager.createPanel<PanelMenuBar>("PanelMenuBar");
        m_panelsManager.createPanel<PanelTestStand>("PanelTestStand");
	}

}