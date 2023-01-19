#include "DragSingleScalar.h"

#include "../imgui/imgui.h"
#include "../imgui/imgui_internal.h"
#include "../imgui/imgui_internal.h"
#include "Helper.h"

namespace TARDIS::UI
{
    DragSingleScalar::DragSingleScalar(
        const std::string& label, 
        const std::string& content, 
        ImGuiDataType dataType, 
        const std::string& range, 
        const std::string& fmt, 
        float speed)
        : DataWidget<std::string>(m_content)
        , m_label(label)
        , m_content(content)
        , m_value(0)
        , m_min(0)
        , m_max(0)
        , m_dataType(dataType)
        , m_speed(speed < 0.000001 ?  1.0f : speed)
        , m_fmt(fmt)
    {
        // this functioan should be called to initialize the "m_value" by "m_content".
        ImGui::DataTypeApplyFromText(m_content.c_str(), m_dataType, (void*)&m_value, ImGui::DataTypeGetInfo(m_dataType)->PrintFmt);
        
        char sRange[2][24] = {0};
        CORE::Helper::SplitString(range.c_str(), ",", sRange);
        ImGui::DataTypeApplyFromText(sRange[0], m_dataType, (void*)&m_min, ImGui::DataTypeGetInfo(m_dataType)->PrintFmt);
        ImGui::DataTypeApplyFromText(sRange[1], m_dataType, (void*)&m_max, ImGui::DataTypeGetInfo(m_dataType)->PrintFmt);
    }

    void DragSingleScalar::drawImpl()
    {
        if(ImGui::DragScalar((m_label + m_widgetID).c_str(), m_dataType, (void*)&m_value, m_speed, &m_min, &m_max, m_fmt.empty() ? (const char*)0 : m_fmt.c_str()))
        {
            char value_buf[64];
            ImGui::DataTypeFormatString(value_buf, IM_ARRAYSIZE(value_buf), m_dataType, (void*)&m_value, ImGui::DataTypeGetInfo(m_dataType)->PrintFmt);
            m_content = value_buf;
            this->notifyChange();
            ChangedEvent.invoke(value_buf);
        }
    }
}