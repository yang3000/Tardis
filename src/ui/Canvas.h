#pragma once

#include "IDrawable.h"
#include "panel/APanel.h"

namespace TARDIS::UI
{
	class Canvas : public IDrawable
	{
	public:
		void addPanel(APanel& p_panel);

		void removePanel(APanel& p_panel);

		void removeAllPanels();

		void makeDockspace(bool p_state);

		bool isDockspace() const;

		void draw() override;

	private:
		std::vector<std::reference_wrapper<APanel>> m_panels;
		bool m_isDockspace = false;
	};
}
