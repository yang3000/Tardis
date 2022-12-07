#include "DragSingleScalar.h"

#include "../imgui/imgui.h"
#include "../imgui/imgui_internal.h"

namespace TARDIS::UI
{
    DragSingleScalar::DragSingleScalar(const std::string& label, const std::string& content, ImGuiDataType dataType, float speed) :
        DataWidget<std::string>(m_content),
        m_label(label),
        m_content(content),
        m_value(0),
        m_dataType(dataType),
        m_speed(speed)
    {}

    void DragSingleScalar::drawImpl()
    {
        if(ImGui::DragScalar((m_label + m_widgetID).c_str(), m_dataType, (void*)&m_value, m_speed))
        {
            char value_buf[64];
            ImGui::DataTypeFormatString(value_buf, IM_ARRAYSIZE(value_buf), m_dataType, (void*)&m_value, ImGui::DataTypeGetInfo(m_dataType)->PrintFmt);
            this->notifyChange();
            ChangedEvent.invoke(value_buf);
        }
    }
}