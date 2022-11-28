#include "APanel.h"

namespace TARDIS::UI
{
	uint64_t APanel::ID_INCREMENT = 0;

	//const std::string APanel::EventOpen("PanelOpen");
	//const std::string APanel::EventClose("PanelClose");

	APanel::APanel()
	{
		m_panelID = "##" + std::to_string(ID_INCREMENT++);
	}

	void APanel::draw()
	{
		drawImpl();
	}

	const std::string& APanel::getPanelID() const
	{
		return m_panelID;
	}
}