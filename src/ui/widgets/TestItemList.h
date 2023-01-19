#pragma once

#include "AWidget.h"

#include <string>

namespace TARDIS::UI
{
	class TestItemList : public AWidget
	{
	protected:
		void drawImpl() override;
	};
}
