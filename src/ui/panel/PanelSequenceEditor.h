#pragma once

#include "APanel.h"
#include "Event.h"

class ImVec4;

namespace TARDIS::CORE
{
    class Runner;
    class Engine;
    class CallBackImpl;
    class SpdLog;
}
namespace TARDIS::UI
{
    class PanelSequenceEditor : public APanel
    {
    public:
        PanelSequenceEditor();
        ~PanelSequenceEditor();

        static void TestStatusButton(const char *id, const ImVec4 &color, bool running);

     public:
        CORE::Event<std::weak_ptr<CORE::Runner>> RunnerSelectedEvent;

    protected:
        void drawImpl() override;

    private:
        //std::unique_ptr<CORE::Engine> m_engine;
        std::shared_ptr<CORE::Engine>       m_engine;
        std::shared_ptr<CORE::CallBackImpl> m_plugin_cb;
        std::shared_ptr<CORE::SpdLog>       m_plugin_log;

    };
}