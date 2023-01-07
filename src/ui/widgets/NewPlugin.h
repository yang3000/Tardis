#pragma once

#include "../AWidget.h"
#include "Event.h"

namespace TARDIS::UI
{
    class NewPlugin : public AWidget
    {
    protected:
        virtual void drawImpl() override;

    public:
        CORE::Event<std::string, std::string> CreatePluginEvent;
    };
}