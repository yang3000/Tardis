#pragma once

#include "AWidget.h"

namespace TARDIS::UI
{
	class Separator : public AWidget
	{
	protected:
		void drawImpl() override;
	};
}
