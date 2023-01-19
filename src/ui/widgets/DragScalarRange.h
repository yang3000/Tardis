#pragma once

#include "DataWidget.h"

#include <string>

#include "Event.h"
#include "../imgui/imgui.h"

namespace TARDIS::UI
{
	class DragScalarRange : public DataWidget<std::string>
	{
	public:
		DragScalarRange(const std::string& label, const std::string& content, const std::string& range, ImGuiDataType dataType, float speed = 0.0f);


	protected:
		void drawImpl() override;


    public:
        CORE::Event<std::string> ChangedEvent;

	private:
		std::string   m_label;

		// holding the initial value.
		std::string   m_content;

		// this is big enough to hold all integers and floating numbers. e.g. long long, double.
		uint64_t      m_current_min;
		uint64_t      m_current_max;

		uint64_t      m_min;
		uint64_t      m_max;

		ImGuiDataType m_dataType;
		float         m_speed;
	};
}
