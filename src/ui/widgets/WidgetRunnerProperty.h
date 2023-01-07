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

        public:
            CORE::Event<std::string> NameChangedEvent;
        private:
            std::weak_ptr<CORE::Runner> m_runner;
    };
}