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

		// 此处写法会导致崩溃
		// 初步分析，widget->draw()在执行过程中，当其中的widget中的子控件触发事件在m_widgets数组中新增元素时破坏此处的for遍历逻辑
		// 相当于在for循环遍历的内部更改m_widgets元素数量，此行为是禁止的
		// 因为这种for循环的使用方式内在实现实际上还是借助迭代器的
        // for (const auto& widget : m_widgets)
		// {
		// 	widget->draw();
		// }
		// 修改成如下调用，没有借助迭代器：
		for(int i = 0; i < m_widgets.size(); i++)
		{
			m_widgets[i]->draw();
		}
            
    }

	std::vector<AWidget*>& WidgetContainer::getWidgets()
	{
		return m_widgets;
	}
}