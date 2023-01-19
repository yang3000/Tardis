#include "PanelProperties.h"

#define IMGUI_DEFINE_MATH_OPERATORS
#include "../imgui/imgui.h"
#include "../imgui/imgui_internal.h"

#include "Runner.h"
#include "../layout/Collapsing.h"
#include "../layout/CollapsingEx.h"
#include "../layout/GroupChild.h"
#include "../widgets/WidgetRunnerProperty.h"
//#include "../plugin/DataDispatcher.h"
#include "../plugin/Callback.h"

namespace TARDIS::UI
{
    PanelProperties::PanelProperties() 
        : PanelWindow("Runner Properties")
        , m_groupChild(createWidget<GroupChild>())
    {}

    void PanelProperties::onSelectedRunner(std::weak_ptr<CORE::Runner> runner)
    {
        static std::vector<std::weak_ptr<CORE::Runner>> cache;
        for(auto& t_runner : cache)
        {
            if(t_runner.lock() == runner.lock()) {
                return;
            }
        }
        cache.emplace_back(runner);

        auto collapsing = &m_groupChild.createWidget<CollapsingEx>(runner.lock()->getName());
       // auto collapsing = &createWidget<CollapsingEx>(runner.lock()->getName());
        collapsing->createWidget<WidgetRunnerProperty>(runner)
        .NameChangedEvent
        .addListener([collapsing](std::string name)
        { 
            collapsing->updateHeader(name); 
        });

        collapsing->addPlugin<Callback>([runner, collapsing]
        { 
            if(!runner.lock()) 
            { 
                collapsing->destroy(); 
            }
        });

        collapsing->CloseEvent
        .addListener([this, runner]
        { 
            cache.erase(std::remove_if(cache.begin(), cache.end(), [runner](auto el)
            { 
                return el.lock() == runner.lock(); 
            }), cache.end());
        });
    }
}