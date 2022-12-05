#pragma once

#include "DataWidget.h"

#include <string>

#include "Event.h"
#include "../imgui/imgui.h"

namespace TARDIS::UI
{
	class DragSingleScalar : public DataWidget<std::string>
	{
	public:
		DragSingleScalar(const std::string& label, const std::string& content, ImGuiDataType dataType, float speed = 1.0f);


	protected:
		void drawImpl() override;


    public:
        CORE::Event<std::string> ChangedEvent;

	private:
		std::string   m_label;
		std::string   m_content;
		uint64_t      m_value;
		ImGuiDataType m_dataType;
		float         m_speed;

	};
}
