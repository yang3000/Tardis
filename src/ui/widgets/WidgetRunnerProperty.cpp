#include "WidgetRunnerProperty.h"

#include "../imgui/imgui.h"

#include "InputText.h"
#include "DragSingleScalar.h"
#include "InputText.h"
#include "HelperMarker.h"
#include "../DataDispatcher.h"

namespace TARDIS::UI
{
    WidgetRunnerProperty::WidgetRunnerProperty(std::weak_ptr<CORE::Runner> runner) : 
        m_runner(runner)
    {
        auto tRunner = m_runner.lock();
        if(tRunner)
        {
            auto params = tRunner->getParams();
            for(auto& p : params)
            {
                //ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1.0f), p->m_name.c_str());
                //ImGui::SameLine();
                //createWidget<InputText>(p->m_name.c_str(), p->m_value.c_str());
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
                    createWidget<DragSingleScalar>(p->m_name.c_str(), p->m_value.c_str(), p->m_typeId);
                    break;
                case TardisDataType_String:
                    createWidget<InputText>(p->m_name.c_str(), p->m_value.c_str(), true);
                    createWidget<HelperMarker>(p->m_desc);
                    
                    break;
                default:
                    break;
                }
                // if(p->m_typeId < TardisDataType_String)
                // {
                //     createWidget<InputText>(p->m_name.c_str(), p->m_value.c_str());
                // }

                // auto& paramWidget = createWidget<DragSingleScalar>(p->m_name.c_str(), "", ImGuiDataType_S8);
                // paramWidget.addPlugin<DataDispatcher<std::string>>().registerReference(p->m_name);
            }
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

    void WidgetRunnerProperty::drawImpl()
	{
		//ImGui::Button("test");
        auto runner = m_runner.lock();
        if(runner)
        {
            ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1.0f), "Params");
            // auto params = runner->getParams();
            // for(auto& p : params)
            // {
            //     ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1.0f), p->m_name.c_str());
            //     ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1.0f), p->m_type.c_str());
            //     ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1.0f), p->m_value.c_str());
            //     ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1.0f), p->m_get.c_str());

            // }
            drawWidgets();
        }
       
	}
}