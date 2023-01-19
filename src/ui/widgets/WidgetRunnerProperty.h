#pragma once

#include "../AWidget.h"
#include "../WidgetContainer.h"

#include "Runner.h"
#include "Event.h"

namespace TARDIS::UI
{
    class WidgetRunnerProperty : public AWidget, public WidgetContainer
    {
    public:
        WidgetRunnerProperty(std::weak_ptr<CORE::Runner> runner);

        ~WidgetRunnerProperty()
        {
            printf("destroy WidgetRunnerProperty\r\n");
        }

    protected:
        virtual void drawImpl() override;

    private:
        bool createNumericalWidget(std::shared_ptr<CORE::Runner::Param> param);
        bool createStringWidget(std::shared_ptr<CORE::Runner::Param> param);
        bool createBoolWidget(std::shared_ptr<CORE::Runner::Param> param);


    public:
        CORE::Event<std::string> NameChangedEvent;

    private:
        std::weak_ptr<CORE::Runner> m_runner;
    };
}