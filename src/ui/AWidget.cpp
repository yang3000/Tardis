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

	const std::string& AWidget::getWidgetId() const
	{
		return m_widgetID;
	}

	AWidget& AWidget::setSameline()
	{
		m_lineBreak = false;
		return *this;
	}
		
	AWidget& AWidget::setWidth(float w)
	{
		m_width = w;
		return *this;
	}

	const float& AWidget::getWidth() const
	{
		return m_width;
	}

	void AWidget::draw()
	{
		if (enabled)
		{
			//ImGui::PushItemWidth(ImGui::CalcItemWidth() * (m_width <= 0.0f ? 1.0f : m_width));
			drawImpl();
			//ImGui::PopItemWidth();

			if (m_autoExecutePlugins)
				executePlugins();

			if (!m_lineBreak)
				ImGui::SameLine();
		}
	}
}