#pragma once

#include "AWidget.h"

#include <string>

#include "Event.h"

namespace TARDIS::UI
{
	class AButton : public AWidget
	{
	protected:
		void drawImpl() override = 0;

    public:
        CORE::Event<> ClickedEvent;
	};
}
