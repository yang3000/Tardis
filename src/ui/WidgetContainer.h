#pragma once

#include <vector>

#if defined(_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable : 4275)
#   pragma warning(disable : 4251)
#endif

namespace TARDIS::UI
{
    class AWidget;

	class WidgetContainer
	{
	public:
		void removeWidget(AWidget& p_widget);

		void removeAllWidgets();

		void unconsiderWidget(AWidget& p_widget);

		void collectGarbages();

		void drawWidgets();

		template <typename T, typename ... Args>
		T& createWidget(Args&&... p_args)
		{
			m_widgets.emplace_back(new T(std::forward<Args>(p_args)...));
			T& instance = *reinterpret_cast<T*>(m_widgets.back());
			instance.setParent(this);
			return instance;
		}

		std::vector<AWidget*>& getWidgets();

	protected:
		std::vector<AWidget*> m_widgets;
	};
}

#if defined(_MSC_VER)
#   pragma warning(pop)
#endif