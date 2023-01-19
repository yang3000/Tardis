#include "WidgetRunnerProperty.h"

#include "../imgui/imgui.h"
#include "../imgui/imgui_internal.h"

#include "Text.h"
#include "CheckBox.h"
#include "ComboBox.h"
#include "DragSingleScalar.h"
#include "DragScalarRange.h"
#include "InputText.h"
#include "Spacing.h"
#include "Separator.h"
#include "HelperMarker.h"
#include "../plugin/DataDispatcher.h"
#include "PluginManager.h"
#include "ValueHelper.h"
#include "../layout/GroupSameline.h"
#include "../layout/Group.h"
#include "../layout/GroupChild.h"
#include "../plugin/Callback.h"

namespace TARDIS::UI
{
    WidgetRunnerProperty::WidgetRunnerProperty(std::weak_ptr<CORE::Runner> runner) : 
        m_runner(runner)
    {
        auto tRunner = m_runner.lock();
        if(tRunner)
        {
            createWidget<InputText>("Name",  tRunner->getName())
            .TextChangedEvent
            .addListener([tRunner, this](std::string name){ tRunner->setName(name); NameChangedEvent.invoke(name);});

            createWidget<CheckBox>("Skip",   tRunner->getSkip());
            createWidget<CheckBox>("Lock",   tRunner->getLock());
            createWidget<CheckBox>("Paused", tRunner->getPaused());

            //createWidget<CheckBox>("Limit").addPlugin<DataDispatcher<bool>>();
            createWidget<Separator>();
            static Group*    pAWidgetLimitGroup = nullptr;
            //static DragScalarRange*  pAWidgetLimit         = nullptr;
            createWidget<CheckBox>("Limit", tRunner->getLimitStatus()).ValueChangedEvent.addListener([](bool isChecked)
            {
                //if(pAWidgetLimit)
                {
                    pAWidgetLimitGroup->enabled = isChecked;
                }
            });
            pAWidgetLimitGroup = &createWidget<Group>();
            pAWidgetLimitGroup->createWidget<ComboBox>("", 11).setWidth(0.5f);
            pAWidgetLimitGroup->createWidget<DragSingleScalar>("Speed", "1.0", ImGuiDataType_Float, "0.01,100.0", "%.5f", 0.01f).setWidth(0.5f);
            pAWidgetLimitGroup->createWidget<DragScalarRange>("Range", "123,456", "0,0", ImGuiDataType_Float);
            pAWidgetLimitGroup->enabled = tRunner->getLimitStatus();
            createWidget<Separator>();

            // pAWidgetDrapSpeed->ChangedEvent.addListener([](std::string value){
            //     pAWidgetLimit
            // });

            //pAWidgetLimit = &createWidget<DragScalarRange>("Float", "123,456", "0,0", ImGuiDataType_Float);



            createWidget<DragScalarRange>("S8", "3,4560", "100,1000", ImGuiDataType_S8);
            createWidget<DragScalarRange>("U8", "3,4560", "100,1000", ImGuiDataType_U8);

            createWidget<DragScalarRange>("S16", "300,4560", "100,1000", ImGuiDataType_S16);
            createWidget<DragScalarRange>("U16", "3,4560", "100,1000", ImGuiDataType_U16);

            createWidget<DragScalarRange>("S32", "3,4560", "100,1000", ImGuiDataType_S32);
            createWidget<DragScalarRange>("U32", "3,4560", "100,1000", ImGuiDataType_U32);

            createWidget<DragScalarRange>("S64", "3,4560", "100,1000", ImGuiDataType_S64);
            createWidget<DragScalarRange>("U64", "3,4560", "100,1000", ImGuiDataType_U64);
            createWidget<DragScalarRange>("Float", "123,456", "100,1000", ImGuiDataType_Float);
            createWidget<DragScalarRange>("Double", "123,456", "100,1000", ImGuiDataType_Double);
            auto& groupSameline = createWidget<GroupSameline>();
            groupSameline.createWidget<DragScalarRange>("", "3,4560", "100,1000", ImGuiDataType_S64).setWidth(0.5f);
            groupSameline.createWidget<DragScalarRange>("", "3,4560", "100,1000", ImGuiDataType_S64).setWidth(0.5f);
            createWidget<ComboBox>("rtyrty").setWidth(0.3f);
            createWidget<Text>(tRunner->getCallerName());

            auto params = tRunner->getParams();
            for(auto& p : params)
            {
                switch (p->m_typeId)
                {
                case TardisDataType_S8:
                case TardisDataType_U8:
                case TardisDataType_S16:
                case TardisDataType_U16:
                case TardisDataType_S32:
                case TardisDataType_U32:
                case TardisDataType_S64:
                case TardisDataType_U64:
                case TardisDataType_Float:
                case TardisDataType_Double:
                case TardisDataType_Bool:
                {
                    // auto& groupSameline = createWidget<GroupSameline>();
                    // groupSameline
                    // .createWidget<DragSingleScalar>("", p->m_value, p->m_typeId, 0.5f)
                    // //.setSameline()
                    // .setWidth(0.7f)
                    // .addPlugin<DataDispatcher<std::string>>()
                    // .registerReference(p->m_value);
                    // groupSameline
                    // .createWidget<InputText>(p->m_name.c_str(), p->m_get.c_str())
                    // .setSameline()
                    // .setWidth(0.3f)
                    // .addPlugin<DataDispatcher<std::string>>()
                    // .registerReference(p->m_get);
                    // createWidget<HelperMarker>(p->m_desc);

                    createNumericalWidget(p);
                    break;
                }
                case TardisDataType_String:
                {
                    auto& groupSameline = createWidget<GroupSameline>();

                    groupSameline
                    .createWidget<InputText>("", p->m_value.c_str())
                    //.setSameline()
                    .setWidth(0.5f)
                    .addPlugin<DataDispatcher<std::string>>()
                    .registerReference(p->m_value);

                    groupSameline
                    .createWidget<InputText>(p->m_name.c_str(), p->m_get.c_str())
                    .setSameline()
                    .setWidth(0.5f)
                    .addPlugin<DataDispatcher<std::string>>()
                    .registerReference(p->m_get);

                    createWidget<HelperMarker>(p->m_desc);
                    break;
                }
                case TardisDataType_Communication:
                {
                    auto& comboBox = createWidget<ComboBox>(p->m_name.c_str(), TARDIS::CORE::ValueHelper<uint64_t>::from(p->m_value));
                   // comboBox.setWidth(0.7f);
                    comboBox.ValueChangedEvent.addListener([p](uint64_t value) { p->m_value = TARDIS::CORE::ValueHelper<uint64_t>::toString(value); });
                    auto& plugins  = TARDIS::CORE::PluginManager::GetPlugins();
                    for(const auto&[id, plugin] : plugins)
                    {
                        comboBox.addElement(id, plugin->getName());
                    }
                    break;
                }

                default:
                    break;
                }


            }

            createWidget<Spacing>();
            createWidget<Spacing>();
        }
        //  createWidget<DragSingleScalar>("TestDrag Char", "12", ImGuiDataType_S8);
        //  createWidget<DragSingleScalar>("TestDrag UChar", "12", ImGuiDataType_U8);
        //  createWidget<DragSingleScalar>("TestDrag Short", "12", ImGuiDataType_S16);
        //  createWidget<DragSingleScalar>("TestDrag UShort", "12", ImGuiDataType_U16);
        //  createWidget<DragSingleScalar>("TestDrag Int", "12", ImGuiDataType_S32);
        //  createWidget<DragSingleScalar>("TestDrag UInt", "12", ImGuiDataType_U32);
        //  createWidget<DragSingleScalar>("TestDrag LLong", "12", ImGuiDataType_S64);
        //  createWidget<DragSingleScalar>("TestDrag ULLong", "12", ImGuiDataType_U64);
        //  createWidget<DragSingleScalar>("TestDrag Float", "12", ImGuiDataType_Float);
        //  createWidget<DragSingleScalar>("TestDrag Double", "12", ImGuiDataType_Double);
    }

    bool WidgetRunnerProperty::createNumericalWidget(std::shared_ptr<CORE::Runner::Param> param)
    {
        auto &groupSameline = createWidget<GroupSameline>();

        groupSameline
            .createWidget<DragSingleScalar>("", param->m_value, param->m_typeId)
            .setWidth(0.7f)
            .addPlugin<DataDispatcher<std::string>>()
            .registerReference(param->m_value);

        groupSameline
            .createWidget<InputText>(param->m_name.c_str(), param->m_get.c_str())
            .setSameline()
            .setWidth(0.3f)
            .addPlugin<DataDispatcher<std::string>>()
            .registerReference(param->m_get);

        createWidget<HelperMarker>(param->m_desc);
        return true;
    }

    void WidgetRunnerProperty::drawImpl()
	{
        auto runner = m_runner.lock();
        if(runner)
        {
            ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1.0f), "Params");
            // static char content[128];
            // ImGui::Button("43453");
            // ImGui::SameLine();
            // ImGui::InputText("345345", content, sizeof(content));
            // ImGui::InputText("345345##111", content, sizeof(content));

            // ImGuiStyle& style = ImGui::GetStyle();
            // float w = IM_FLOOR((ImGui::CalcItemWidth() - style.ItemSpacing.x) * 0.7f);
            // ImGui::PushItemWidth(w);
			// ImGui::InputText("##23", content, sizeof(content));
			// ImGui::PopItemWidth();
            // ImGui::SameLine();
            // ImGui::PushItemWidth(ImGui::CalcItemWidth() - w - style.ItemSpacing.x);
			// ImGui::InputText("345345##2322", content, sizeof(content));
			// ImGui::PopItemWidth();

            // static float vec4f[4] = { 0.10f, 0.20f, 0.30f, 0.44f };
            // ImGui::DragFloat2("drag float2", vec4f, 0.01f, 0.0f, 1.0f);

            drawWidgets();
        }
	}
}