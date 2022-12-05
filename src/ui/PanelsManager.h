#pragma once

#include <unordered_map>
#include <memory>

#include "./panel/APanel.h"
#include "Canvas.h"

namespace TARDIS::UI
{
	class PanelsManager
	{
	public:
	    PanelsManager(Canvas& canvas) : m_canvas(canvas) {}

		template<typename T, typename... Args>
		void createPanel(const std::string& p_id, Args&&... p_args)
		{
			//m_panels.emplace(p_id, std::make_unique<T>(p_id, std::forward<Args>(p_args)...));
			m_panels.emplace(p_id, std::make_unique<T>(std::forward<Args>(p_args)...));
			m_canvas.addPanel(*m_panels.at(p_id));
			//return *static_cast<T*>(m_panels[p_id].get());
			//GetPanelAs<OvEditor::Panels::MenuBar>("Menu Bar").RegisterPanel(instance.name, instance);
		}

		template<typename T>
		T& getPanelAs(const std::string& p_id)
		{
			return *static_cast<T*>(m_panels[p_id].get());
		}

	private:
		using PanelMap = std::unordered_map<std::string, std::unique_ptr<APanel>>;

		PanelMap m_panels;
		Canvas&  m_canvas;
	};
}
