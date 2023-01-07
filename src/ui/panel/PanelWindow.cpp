#include "PanelWindow.h"

#include "../imgui/imgui.h"

namespace TARDIS::UI
{
	//const std::string PanelWindow::EventOpen("PanelOpen");
	//const std::string PanelWindow::EventClose("PanelClose");

	PanelWindow::PanelWindow(const std::string& name, bool opened) :
		m_name(name),
		m_opened(opened)
	{

	}

	PanelWindow::~PanelWindow()
	{
		printf("destroy PanelWindow\r\n");
	}

	void PanelWindow::setOpened(bool show)
	{
		if (m_opened != show)
		{
			m_opened = show;

			if (m_opened)
			{
				PanelOpenEvent.invoke();
			}
			else
			{
				PanelCloseEvent.invoke();
			}
		}
	}

	bool PanelWindow::isOpened()
	{
		return m_opened;
	}

	void PanelWindow::drawImpl()
	{
		if (m_opened)
		{
			ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;// ImGuiWindowFlags_MenuBar;
			//window_flags |= ImGuiWindowFlags_NoTitleBar;
			//if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
			//if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
			//if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
			//if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
			//if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
			//if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
			//if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
			//if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
			//if (no_docking)         window_flags |= ImGuiWindowFlags_NoDocking;
			//if (unsaved_document)   window_flags |= ImGuiWindowFlags_UnsavedDocument;
			//static bool open = true;

			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 4.0f));
			ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, 16.0f);

			

			if (ImGui::Begin((m_name + m_panelID).c_str(), &m_opened, window_flags))
			{
				if (!m_opened)
				{
					PanelCloseEvent.invoke();
				}
				

				drawWidgets();
				ImGui::End();
			}
			        ImGui::PopStyleVar(2);

		}
	}
}