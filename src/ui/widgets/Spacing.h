#pragma once

#include "AWidget.h"

namespace TARDIS::UI
{
	class Spacing : public AWidget
	{
	protected:
		void drawImpl() override;
	};
}
