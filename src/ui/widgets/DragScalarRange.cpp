#include "DragScalarRange.h"

#include "../imgui/imgui.h"
#include "../imgui/imgui_internal.h"
#include "Helper.h"

namespace TARDIS::UI
{
    DragScalarRange::DragScalarRange(const std::string& label, const std::string& content, const std::string& range, ImGuiDataType dataType, float speed) 
        : DataWidget<std::string>(m_content)
        , m_label(label)
        , m_content(content)
        , m_current_min(0)
        , m_current_max(0)
        , m_min(0)
        , m_max(0)
        , m_dataType(dataType)
        , m_speed(speed < 0.000001 ?  1.0f : speed)
    {
        // this functioan should be called to initialize the "m_value" by "m_content".

        char sCurrent[2][24] = {0};
        CORE::Helper::SplitString(m_content.c_str(), ",", sCurrent);
        ImGui::DataTypeApplyFromText(sCurrent[0], m_dataType, (void*)&m_current_min, ImGui::DataTypeGetInfo(m_dataType)->PrintFmt);
        ImGui::DataTypeApplyFromText(sCurrent[1], m_dataType, (void*)&m_current_max, ImGui::DataTypeGetInfo(m_dataType)->PrintFmt);

        char sRange[2][24] = {0};
        CORE::Helper::SplitString(range.c_str(), ",", sRange);
        ImGui::DataTypeApplyFromText(sRange[0], m_dataType, (void*)&m_min, ImGui::DataTypeGetInfo(m_dataType)->PrintFmt);
        ImGui::DataTypeApplyFromText(sRange[1], m_dataType, (void*)&m_max, ImGui::DataTypeGetInfo(m_dataType)->PrintFmt);

        //CORE::Helper::MinValue;
        if(ImGui::DataTypeCompare(m_dataType, (void*)&m_min, (void*)&m_max) >= 0)
        {
            CORE::Helper::MinValue((TardisDataType)m_dataType , (void*)&m_min);
            CORE::Helper::MaxValue((TardisDataType)m_dataType , (void*)&m_max);
        }

        // if(ImGui::DataTypeCompare(m_dataType, (void*)&m_min, (void*)&m_current_min) > 0)
        // {
        //     m_min = m_current_min;
        // }

        // if(ImGui::DataTypeCompare(m_dataType, (void*)&m_current_max, (void*)&m_max) > 0)
        // {
        //     m_max = m_current_max;
        // }

    }

    void DragScalarRange::drawImpl()
    {

        // char aa[12];
        // ImGui::InputText("", aa, 12);
        // ImGui::SameLine();

        //         static float begin = 10, end = 90;
        // static int begin_i = 100, end_i = 1000;
        // ImGui::DragFloatRange2("3232", &begin, &end, 0.25f, 0.0f, 100.0f, "Min: %.1f %%", "Max: %.1f %%", ImGuiSliderFlags_AlwaysClamp);
        // return;
        ImGuiWindow *window = ImGui::GetCurrentWindow();
        if (window->SkipItems)
            return;

        ImGuiContext &g = *GImGui;
        ImGui::PushID(m_label.c_str());
        ImGui::BeginGroup();
        ImGui::PushMultiItemsWidths(2, ImGui::CalcItemWidth());

        ImGuiSliderFlags min_flags = (m_min == m_current_max) ? ImGuiSliderFlags_ReadOnly : 0;
        bool value_changed =  ImGui::DragScalar("##min", m_dataType, &m_current_min, 1.0f, &m_min, &m_current_max, ImGui::DataTypeGetInfo(m_dataType)->PrintFmt, min_flags);
        ImGui::PopItemWidth();
        ImGui::SameLine(0, g.Style.ItemInnerSpacing.x);

        ImGuiSliderFlags max_flags = (m_current_min == m_max) ? ImGuiSliderFlags_ReadOnly : 0;
        value_changed |= ImGui::DragScalar("##max", m_dataType, &m_current_max, 1.0f, &m_current_min, &m_max, ImGui::DataTypeGetInfo(m_dataType)->PrintFmt, max_flags);
        ImGui::PopItemWidth();
        ImGui::SameLine(0, g.Style.ItemInnerSpacing.x);

        if(m_label.size())
            ImGui::TextEx(m_label.c_str(), ImGui::FindRenderedTextEnd(m_label.c_str()));

        ImGui::EndGroup();
        ImGui::PopID();

        if(value_changed)
        {
            char value_min_buf[64];
            char value_max_buf[64];
            ImGui::DataTypeFormatString(value_min_buf, IM_ARRAYSIZE(value_min_buf), m_dataType, (void *)&m_current_min, ImGui::DataTypeGetInfo(m_dataType)->PrintFmt);
            ImGui::DataTypeFormatString(value_max_buf, IM_ARRAYSIZE(value_max_buf), m_dataType, (void *)&m_current_max, ImGui::DataTypeGetInfo(m_dataType)->PrintFmt);
            char range_buf[128];
            sprintf_s(range_buf, sizeof(range_buf), "%s,%s", value_min_buf, value_max_buf);
            ChangedEvent.invoke(range_buf);
        }


// if(ImGui::DragScalar((m_label + m_widgetID).c_str(), m_dataType, (void*)&m_value, m_speed))
//         {
//             char value_buf[64];
//             ImGui::DataTypeFormatString(value_buf, IM_ARRAYSIZE(value_buf), m_dataType, (void*)&m_value, ImGui::DataTypeGetInfo(m_dataType)->PrintFmt);
//             m_content = value_buf;
//             this->notifyChange();
//             ChangedEvent.invoke(value_buf);
//         }
//         return value_changed;
        }
}