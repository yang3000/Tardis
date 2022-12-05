#pragma once

#include "APanel.h"
#include "Event.h"

class ImVec4;

namespace TARDIS::CORE
{
    class Runner;
}
namespace TARDIS::UI
{
    class PanelSequenceEditor : public APanel
    {
    public:
        PanelSequenceEditor();

        static void TestStatusButton(const char *id, const ImVec4 &color, bool running);

     public:
        CORE::Event<std::weak_ptr<CORE::Runner>> RunnerSelectedEvent;

    protected:
        void drawImpl() override;

    };
}