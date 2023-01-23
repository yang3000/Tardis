#pragma once

#include "APanel.h"
#include "Event.h"
#include <memory>

class ImVec4;

namespace TARDIS::CORE
{
    class Runner;
    class Engine;
    class CallBackImpl;
    class SpdLog;
    class RapidJsonParser;

    struct TestItemResult;
}
namespace TARDIS::UI
{


    class PanelTestStand : public APanel
    {
    public:
        PanelTestStand();
        ~PanelTestStand();

        void onAddTestResult(CORE::TestItemResult* result);

    protected:
        void drawImpl() override;

    private:

        bool                                   m_engineIsRunning;
        std::vector<std::shared_ptr<CORE::TestItemResult>> m_testItemList;
        //std::unique_ptr<CORE::Engine> m_engine;
        std::shared_ptr<CORE::Engine>          m_engineRunTest;

        std::shared_ptr<CORE::Engine>          m_engineSetup;

        std::shared_ptr<CORE::Engine>          m_engineCleanup;

        std::shared_ptr<CORE::CallBackImpl>    m_plugin_cb;

        std::shared_ptr<CORE::SpdLog>          m_plugin_log;

        std::shared_ptr<CORE::SpdLog>          m_globalPluginLog;

        std::shared_ptr<CORE::RapidJsonParser> m_json_parser;
    };
}