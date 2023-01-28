#pragma once

#include "Window.h"
#include "Canvas.h"
#include "PanelsManager.h"


namespace TARDIS::CORE
{
    class SpdLog;
    class RapidJsonParser;
}

namespace TARDIS::UI
{
	class GroupTable;

	class WindowTestStand : public Window
	{
	public:
		WindowTestStand();

		~WindowTestStand();
        
		void setupUI();

		void loadTestSequences();

		void addTest();

    private:
        std::shared_ptr<CORE::RapidJsonParser> m_jsonParser;
        GroupTable* m_testBoards;

	};
}