#include "PanelProperties.h"

#define IMGUI_DEFINE_MATH_OPERATORS
#include "../imgui/imgui.h"
#include "../imgui/imgui_internal.h"

#include "Runner.h"
#include "../layout/Collapsing.h"
#include "../widgets/WidgetRunnerProperty.h"
#include "../DataDispatcher.h"

namespace TARDIS::UI
{

    PanelProperties::PanelProperties() : PanelWindow("Properties")
    {}

    void PanelProperties::onSelectedRunner(std::weak_ptr<CORE::Runner> runner)
    {
        static std::vector<std::weak_ptr<CORE::Runner>> cache;

        for(auto& el : cache)
        {
            if(el.lock() == runner.lock())
            {
                return;
            }
        }

        cache.emplace_back(runner);

        auto& collapsing = createWidget<Collapsing>(runner.lock()->getName());
        auto& runnerProp = collapsing.createWidget<WidgetRunnerProperty>(runner);
        // auto& plugin     = runnerProp.addPlugin<DataDispatcher<std::string>>();
        // plugin.registerReference()
        
        collapsing.CloseEvent.addListener([runner] () 
        { 
            cache.erase(std::remove_if(cache.begin(), cache.end(), [runner](auto el) { return  el.lock() == runner.lock(); }), cache.end()); 
        });
    }
}