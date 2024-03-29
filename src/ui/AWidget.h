#pragma once

#include <string>

#include "IDrawable.h"
#include "Pluginable.h"

#if defined(_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable : 4275)
#   pragma warning(disable : 4251)
#endif

namespace  TARDIS::UI { class WidgetContainer; }

namespace TARDIS::UI
{
	class AWidget : public IDrawable, public Pluginable
	{
	public:
		AWidget();

		virtual void draw() override;

		void linkTo(const AWidget& p_widget);

		void destroy();

		bool isDestroyed() const;

		void setParent(WidgetContainer* p_parent);

		bool hasParent() const;

		WidgetContainer* getParent();

		const std::string& getWidgetId() const;

		AWidget& setSameline();
		
		AWidget& setWidth(float w);

		const float& getWidth() const;

	protected:
		virtual void drawImpl() = 0;

	public:
		bool  enabled = true;
		

	protected:
		WidgetContainer* m_parent;
		std::string m_widgetID = "#-1";
		bool  m_autoExecutePlugins = true;
		

	private:
		static uint64_t ID_INCREMENT;
		bool  m_destroyed = false;
		bool  m_lineBreak = true;
		float m_width = 0.0f;

	};
}

#if defined(_MSC_VER)
#   pragma warning(pop)
#endif