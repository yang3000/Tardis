#pragma once

#include "PanelWindow.h"
#include "../layout/Collapsing.h"
#include "../layout/GroupChild.h"

#include <memory>
#include <vector>

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

    
    private:
        GroupChild& m_groupChild;
    };
}