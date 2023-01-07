#include "PanelPluginManager.h"

#include <tuple>
#define IMGUI_DEFINE_MATH_OPERATORS
#include "../imgui/imgui.h"
#include "../imgui/imgui_internal.h"

#include "../layout/Collapsing.h"
#include "../layout/CollapsingEx.h"
#include "../layout/TreeNode.h"
#include "../DataDispatcher.h"
#include "../plugin/Callback.h"
#include "../plugin/DDSource.h"
#include "../widgets/InputText.h"
#include "../widgets/Button.h"
#include "../widgets/Spacing.h"
#include "../widgets/Text.h"
#include "../widgets/Separator.h"
#include "../widgets/LabelText.h"
#include "../widgets/TextColored.h"
#include "../widgets/Caller.h"
#include "../widgets/NewPlugin.h"
#include "../layout/GroupChild.h"

#include "PluginManager.h"
#include "SpdLog.h"
#include "Runner.h"
#include "ValueHelper.h"


namespace TARDIS::UI
{
    CORE::Event<const char *, Param *, unsigned> PanelPluginManager::LoadCallerEvent;

    PanelPluginManager::PanelPluginManager() 
        : PanelWindow("Plugin Manager")
    {
        createWidget<Button>("Create").ClickedEvent.addListener([]()
        {
            ImGui::OpenPopup("New Plugin");
        });
        createWidget<NewPlugin>().CreatePluginEvent.addListener([](std::string name, std::string path)
        {
            CORE::PluginManager::LoadPlugin(name, path);
        });
        createWidget<Separator>();
        m_groupChild = &createWidget<GroupChild>();
        //m_groupChild->createWidget<Spacing>();
    }

    void PanelPluginManager::onAddPlugin(uint64_t pluginId, std::shared_ptr<CORE::PluginContainer> pluginContainer)
    {
        auto header = &m_groupChild->createWidget<CollapsingEx>(pluginContainer->getName());
        // header->setPopupFn([pluginId, header]()
        // {
        //     if (ImGui::MenuItem("Remove"))
        //     {
        //         CORE::PluginManager::DestroyPlugin(pluginId);
        //         header->setClosed();
        //     }

        //     if (ImGui::MenuItem("Clone"))
        //     {
        //         CORE::PluginManager::ClonePlugin(pluginId);
        //     }
        // });

        // header->CloneEvent.addListener([pluginId](){
        //         CORE::PluginManager::ClonePlugin(pluginId);
        // });
        header->createWidget<Button>("clone").ClickedEvent.addListener([pluginId](){
                CORE::PluginManager::ClonePlugin(pluginId);

        });
        header->createWidget<TextColored>("Base Information", ImVec4(0.5f, 0.5f, 0.5f, 1.0f));
        header->createWidget<InputText>("Module", pluginContainer->getName());
        header->createWidget<LabelText>("Path", pluginContainer->getFilePath());
        header->createWidget<TextColored>("Description", ImVec4(0.5f, 0.5f, 0.5f, 1.0f));
        header->createWidget<Text>(pluginContainer->getDesc().empty() ? "null" : pluginContainer->getDesc());
        header->createWidget<Separator>();
        auto callers = &header->createWidget<TreeNode>("Callers");

        LoadCallerEvent.removeAllListeners();
        LoadCallerEvent.addListener([callers, pluginId](const char *name, Param *params, unsigned count)
        {
            auto runner = std::make_shared<CORE::Runner>();
            runner->setModuleId(pluginId);
            runner->setCallerName(name);
            runner->setName(name);
            for (unsigned i = 0; i < count; ++i)
            {
                TDS_LOG_INFO("{}:{}[{}]:{}", i, params[i].name.buf, params[i].type.buf, params[i].desc.buf);
                runner->addParam(std::string(params[i].name.buf, params[i].name.len), "", "",
                                 std::string(params[i].desc.buf, params[i].desc.len),
                                 std::string(params[i].type.buf, params[i].type.len),
                                 CORE::ValueHelper<UInt>::from(std::string(params[i].typeId.buf, params[i].typeId.len)));
            }
            auto& caller = callers->createWidget<Caller>(name);
            caller.addPlugin<DDSource<std::shared_ptr<CORE::Runner>>>("AddTestItem", name, runner); 
        });

        pluginContainer->get(0)->parseCallerInfo([](const char *name, Param *params, unsigned count)
        { 
            PanelPluginManager::LoadCallerEvent.invoke(name, params, count); 
        });
    }
}