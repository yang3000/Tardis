#pragma once

#include <vector>

#include "PanelWindow.h"

namespace TARDIS::CORE
{
    class Runner;
}

namespace TARDIS::UI
{
    class PanelProperties : public PanelWindow
    {
    public:
        PanelProperties();

        void onSelectedRunner(std::weak_ptr<CORE::Runner> runner);
    };
}