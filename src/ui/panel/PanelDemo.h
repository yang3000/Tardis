#pragma once

#include "PanelWindow.h"
#include "../layout/Collapsing.h"
#include "Base.h"
#include "Event.h"

#include <vector>
#include <memory>

namespace TARDIS::UI
{
    class PanelDemo : public PanelWindow
    {
    protected:
		void drawImpl() override;
    public:
        PanelDemo();
    };
}