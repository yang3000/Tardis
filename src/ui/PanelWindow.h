#pragma once

#include "panel/APanel.h"

namespace TARDIS::UI
{
	class PanelWindow : public APanel
	{
	public:
		// static const std::string EventOpen;

		// static const std::string EventClose;

		PanelWindow(const std::string& name = "", bool opened = true);

		~PanelWindow();

		void setOpened(bool show);

		bool isOpened();

	protected:
		void drawImpl() override;

	private:
		bool              m_opened;
		std::string       m_name;
	};
}