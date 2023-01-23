#pragma once

#include "PanelWindow.h"
#include "../layout/Collapsing.h"
#include "Base.h"
#include "Event.h"

#include <vector>
#include <memory>

namespace TARDIS::CORE
{
   // class Runner;
   class PluginContainer;
}


namespace TARDIS::UI
{
    class GroupChild;

    class PanelPluginManager : public PanelWindow
    {
    public:
        PanelPluginManager();

        void onAddPlugin(uint64_t pluginId, std::shared_ptr<CORE::PluginContainer> pluginContainer);

    public:
        static CORE::Event<const char *, Param *, unsigned> LoadCallerEvent;

    private:
        GroupChild* m_groupChild;
    };
}