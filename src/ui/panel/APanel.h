#pragma once

#include <string>
#include <vector>
#include <unordered_map>
//#include "../../core/include/EventSet.h"
#include "../IDrawable.h"
#include "../WidgetContainer.h"

#if defined(_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable : 4275)
#   pragma warning(disable : 4251)
#endif

namespace TARDIS::UI
{
	class APanel :
		public IDrawable,
		public WidgetContainer
	{
	public:

		APanel();
		~APanel()
		{
			printf("destroy APanel\r\n");
		}

		void draw() override;

		const std::string& getPanelID() const;

	protected:
		virtual void drawImpl() = 0;

		std::string m_panelID;

	private:
		static uint64_t ID_INCREMENT;

	};
}

#if defined(_MSC_VER)
#   pragma warning(pop)
#endif