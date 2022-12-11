#pragma once

#include "APanel.h"
#include "Event.h"

namespace TARDIS::UI
{
	class PanelWindow : public APanel
	{
	public:
		PanelWindow(const std::string& name = "", bool opened = true);

		~PanelWindow();

		void setOpened(bool show);

		bool isOpened();

  	public:
        CORE::Event<> PanelOpenEvent;
        CORE::Event<> PanelCloseEvent;

	protected:
		void drawImpl() override;

	private:
		bool              m_opened;
		std::string       m_name;
	};
}