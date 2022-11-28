#include "AWidget.h"

#include "imgui/imgui.h"

namespace TARDIS::UI
{
	uint64_t AWidget::ID_INCREMENT = 0;

	AWidget::AWidget()
	{
		m_widgetID = "##" + std::to_string(ID_INCREMENT++);
	}

	void AWidget::linkTo(const AWidget& p_widget)
	{
		m_widgetID = p_widget.m_widgetID;
	}

	void AWidget::destroy()
	{
		m_destroyed = true;
	}

	bool AWidget::isDestroyed() const
	{
		return m_destroyed;
	}

	void AWidget::setParent(WidgetContainer* p_parent)
	{
		m_parent = p_parent;
	}

	bool AWidget::hasParent() const
	{
		return m_parent;
	}

	WidgetContainer* AWidget::getParent()
	{
		return m_parent;
	}

	void AWidget::draw()
	{
		if (enabled)
		{
			drawImpl();

			// if (m_autoExecutePlugins)
			// 	executePlugins();

			if (!lineBreak)
				ImGui::SameLine();
		}
	}
}