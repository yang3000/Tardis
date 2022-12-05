#include "WidgetContainer.h"

#include <algorithm>

#include "AWidget.h"

namespace TARDIS::UI
{

    WidgetContainer::~WidgetContainer()
    {
        removeAllWidgets();
    }
	void WidgetContainer::removeWidget(AWidget& p_widget)
	{
		auto found = std::find_if(m_widgets.begin(), m_widgets.end(), [&p_widget](AWidget*& widget)
		{
			return widget == &p_widget;
		});

		if (found != m_widgets.end())
		{
			delete *found;
			m_widgets.erase(found);
		}
	}

	void WidgetContainer::removeAllWidgets()
	{
		std::for_each(m_widgets.begin(), m_widgets.end(), [](AWidget*& widget)
		{
			delete widget;
		});

		m_widgets.clear();
	}

	void WidgetContainer::unconsiderWidget(AWidget& p_widget)
	{
		auto found = std::find_if(m_widgets.begin(), m_widgets.end(), [&p_widget](AWidget*& widget)
		{
			return widget == &p_widget;
		});

		if (found != m_widgets.end())
		{
			p_widget.setParent(nullptr);
			m_widgets.erase(found);
		}
	}

	void WidgetContainer::collectGarbages()
	{
		m_widgets.erase(std::remove_if(m_widgets.begin(), m_widgets.end(), [](AWidget*& widget)
		{
			bool toDestroy = widget->isDestroyed();
			if (toDestroy)
			{
                printf("collectGarbages\r\n");
				delete widget;
			}
			return toDestroy;
		}), m_widgets.end());
	}

	void WidgetContainer::drawWidgets()
	{
        collectGarbages();

        for (const auto &widget : m_widgets)
            widget->draw();
    }

	std::vector<AWidget*>& WidgetContainer::getWidgets()
	{
		return m_widgets;
	}
}