#pragma once

#include "../AWidget.h"
#include "../WidgetContainer.h"
#include "Runner.h"

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
            std::weak_ptr<CORE::Runner> m_runner;
    };
}