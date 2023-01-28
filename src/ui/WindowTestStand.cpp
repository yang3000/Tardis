#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"

#include "WindowTestStand.h"
#include "panel/PanelWindow.h"
#include "panel/PanelMenuBar.h"
#include "panel/PanelTestStand.h"
#include "panel/PanelProperties.h"
#include "panel/PanelPluginManager.h"
#include "PanelsManager.h"
#include "IconsFontAwesome5.h"
#include "Runner.h"
//#include "EngineManager.h"
#include "PluginManager.h"
#include "layout/GroupTable.h"
#include "layout/Group.h"
#include "layout/GroupChild.h"
#include "widgets/Text.h"
#include "widgets/Button.h"
#include "widgets/TestBoard.h"
#include "SpdLog.h"

#include "Engine.h"
#include "PluginManager.h"

//#include "RapidJsonParser.h"
//#include "RunnerProperty.h"


namespace TARDIS::UI
{
	WindowTestStand::WindowTestStand()
	{
		setupUI();
	}

	WindowTestStand::~WindowTestStand()
	{
	}


	void WindowTestStand::setupUI()
	{
        m_panelsManager.createPanel<PanelMenuBar>("PanelMenuBar");
        m_panelsManager.createPanel<PanelTestStand>("PanelTestStand");
        m_panelsManager.createPanel<PanelWindow>("PanelWindowTestBoard", "Test Board");

		m_testBoards = &m_panelsManager.getPanelAs<PanelWindow>("PanelWindowTestBoard").createWidget<GroupTable>();
	}

	void WindowTestStand::loadTestSequences()
	{
        m_jsonParser = std::make_shared<CORE::RapidJsonParser>();
        m_jsonParser->parseJsonFile("sequence.json");
        TDS_LOG_INFO(m_jsonParser->get("version"));

		for(int i = 0; i < 8; ++i)
		{
			addTest();
		}

		CORE::PluginManager::OnDeserialize(m_jsonParser);
        CORE::Engine::OnDeserialize(m_jsonParser);
	}

	void WindowTestStand::addTest()
	{
		m_testBoards->createWidget<TestBoard>();
	}

}