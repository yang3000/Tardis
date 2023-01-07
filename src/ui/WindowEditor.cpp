#include "imgui/imgui.h"
//#include "imgui/imgui_impl_glfw.h"
//#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_internal.h"
//#include <GLFW/glfw3.h>

//#include "PanelsManager.h"
#include "WindowEditor.h"
//#include "PanelWindow.h"
#include "panel/PanelMenuBar.h"
#include "panel/PanelSequenceEditor.h"
#include "panel/PanelProperties.h"
#include "panel/PanelPluginManager.h"
#include "PanelsManager.h"
//#include "SequenceEditView.h"
//#include "ModulesView.h"
//#include "BurnInView.h"
//#include "TestView.h"
#include "IconsFontAwesome5.h"
#include "Runner.h"
//#include "EngineManager.h"
#include "PluginManager.h"
//#include "RapidJsonParser.h"
//#include "RunnerProperty.h"


namespace TARDIS::UI
{
	WindowEditor::WindowEditor()
	{
		//CORE::EngineManager::Create();
		//CORE::PluginManager::Create();

		setup();
	}
	WindowEditor::~WindowEditor()
	{
		//CORE::EngineManager::Destroy();
		//CORE::PluginManager::Destroy();
	}


	void WindowEditor::setup()
	{
		//UI::PanelWindow& panelWindow = UI::PanelsManager::CreatePanel<UI::PanelWindow>("hhh");
		//panelWindow.subscribeEvent()
		//addPanel(UI::PanelsManager::CreatePanel<UI::PanelWindow>("MyFirstPanel"));
        //static PanelsManager panelsManager;
        //static PanelMenuBar panelMenuBar;
        //static PanelSequenceEditor panelSequenceEditor;
        //static PanelProperties panelProperties;
		//addPanel(panelMenuBar);
		//addPanel(panelSequenceEditor);
		//addPanel(panelProperties);
        //panelsManager.CreatePanel
        // panelSequenceEditor.RunnerSelectedEvent.addListener([](std::weak_ptr<CORE::Runner> runner){
        //     printf(runner.lock()->getName().c_str());
        //     panelProperties.onSelectedRunner(runner);
        // });
        m_panelsManager.createPanel<PanelMenuBar>("PanelMenuBar");
        m_panelsManager.createPanel<PanelSequenceEditor>("PanelSequenceEditor");
        m_panelsManager.createPanel<PanelProperties>("PanelProperties");

        m_panelsManager.getPanelAs<PanelSequenceEditor>("PanelSequenceEditor").RunnerSelectedEvent.addListener([this](std::weak_ptr<CORE::Runner> runner){
            printf(runner.lock()->getName().c_str());
            printf("\r\n");
            m_panelsManager.getPanelAs<PanelProperties>("PanelProperties").onSelectedRunner(runner);
            //panelProperties.onSelectedRunner(runner);
        });

        m_panelsManager.createPanel<PanelPluginManager>("PanelPluginManager");

		auto  panelPluginManager = &m_panelsManager.getPanelAs<PanelPluginManager>("PanelPluginManager");
		auto &plugins = CORE::PluginManager::GetPlugins();
		for (auto &[id, pluginContainer] : plugins)
		{
			panelPluginManager->onAddPlugin(id, pluginContainer);
		}

		CORE::PluginManager::LoadPluginEvent.addListener([panelPluginManager](uint64_t pluginId, std::shared_ptr<CORE::PluginContainer> container)
        {
            panelPluginManager->onAddPlugin(pluginId, container);
        });
		

		// static std::shared_ptr<CORE::RapidJsonParser> parser = std::make_shared<CORE::RapidJsonParser>();
		// parser->parseJsonFile("C:\\Users\\yangh\\Desktop\\Tardis\\bin\\Debug\\sequence.json");

		// addPanel(UI::PanelsManager::CreatePanel<UI::SequenceEditView>("SequenceEditView"));
		// addPanel(UI::PanelsManager::CreatePanel<UI::ModulesView>("ModulesView"));
		// addPanel(UI::PanelsManager::CreatePanel<UI::RunnerProperty>("RunnerProperty"));



		// std::string testName = parser->get<std::string>("sequences/name");


		// auto& panel = UI::PanelsManager::GetPanelAs<UI::SequenceEditView>("SequenceEditView");

		// auto& panel_modules_view = UI::PanelsManager::GetPanelAs<UI::ModulesView>("ModulesView");

		// parser->nodeBegin("modules");
		// panel_modules_view.onDeserialize(parser);
		// parser->nodeEnd();

		// if (parser->nodeBegin("sequences"))
		// {
		// 	CORE::Engine::onDeserialize(parser);
		// 	parser->nodeEnd();
		// }
		// auto& property = UI::PanelsManager::GetPanelAs<UI::RunnerProperty>("RunnerProperty");
		// property.addRunner(CORE::Engine::runnerList[0]);

	/*	parser->nodeBegin("sequences");
		panel.onDeserialize(parser);
		parser->nodeEnd();*/

		//addPanel(UI::PanelsManager::CreatePanel<UI::BurnInView>("BurnInView"));
		//addPanel(UI::PanelsManager::CreatePanel<UI::TestView>("TestView"));
		//addPanel(UI::PanelsManager::CreatePanel<UI::TestView>("TestView"));
		//ImGuiContext* ctx = ImGui::GetCurrentContext();
		//ImGuiDockContext* dc = &ctx->DockContext;
		//ImGui::SaveIniSettingsToMemory();
		//ImGuiID root_id = 0; // Rebuild all
		//ImGui::DockContextClearNodes(ctx, root_id, false);

		////ImGui::DockContextBuildNodesFromSettings(ctx, dc->NodesSettings.Data, dc->NodesSettings.Size);

		//ImGuiDockNodeSettings* node_settings_array = dc->NodesSettings.Data;
		//int node_settings_count = dc->NodesSettings.Size;
		//for (int node_n = 0; node_n < node_settings_count; node_n++)
		//{
		//	ImGuiDockNodeSettings* settings = &node_settings_array[node_n];
		//	if (settings->ID == 0)
		//		continue;
		//	ImGuiDockNode* node = DockContextAddNode(ctx, settings->ID);
		//	node->ParentNode = settings->ParentNodeId ? DockContextFindNodeByID(ctx, settings->ParentNodeId) : NULL;
		//	node->Pos = ImVec2(settings->Pos.x, settings->Pos.y);
		//	node->Size = ImVec2(settings->Size.x, settings->Size.y);
		//	node->SizeRef = ImVec2(settings->SizeRef.x, settings->SizeRef.y);
		//	node->AuthorityForPos = node->AuthorityForSize = node->AuthorityForViewport = ImGuiDataAuthority_DockNode;
		//	if (node->ParentNode && node->ParentNode->ChildNodes[0] == NULL)
		//		node->ParentNode->ChildNodes[0] = node;
		//	else if (node->ParentNode && node->ParentNode->ChildNodes[1] == NULL)
		//		node->ParentNode->ChildNodes[1] = node;
		//	node->SelectedTabId = settings->SelectedTabId;
		//	node->SplitAxis = (ImGuiAxis)settings->SplitAxis;
		//	node->SetLocalFlags(settings->Flags & ImGuiDockNodeFlags_SavedFlagsMask_);

		//	// Bind host window immediately if it already exist (in case of a rebuild)
		//	// This is useful as the RootWindowForTitleBarHighlight links necessary to highlight the currently focused node requires node->HostWindow to be set.
		//	char host_window_title[20];
		//	ImGuiDockNode* root_node = DockNodeGetRootNode(node);
		//	node->HostWindow = FindWindowByName(DockNodeGetHostWindowTitle(root_node, host_window_title, IM_ARRAYSIZE(host_window_title)));
		//}

		//ImGui::DockContextBuildAddWindowsToNodes(context, root_id);
	}

	void WindowEditor::setDockSpaceBegin()
	{
		//-----------------------------------------------------------------------------
		// [SECTION] Example App: Docking, DockSpace / ShowExampleAppDockSpace()
		//-----------------------------------------------------------------------------

		// Demonstrate using DockSpace() to create an explicit docking node within an existing window.
		// Note: You can use most Docking facilities without calling any API. You DO NOT need to call DockSpace() to use Docking!
		// - Drag from window title bar or their tab to dock/undock. Hold SHIFT to disable docking.
		// - Drag from window menu button (upper-left button) to undock an entire node (all windows).
		// - When io.ConfigDockingWithShift == true, you instead need to hold SHIFT to _enable_ docking/undocking.
		// About dockspaces:
		// - Use DockSpace() to create an explicit dock node _within_ an existing window.
		// - Use DockSpaceOverViewport() to create an explicit dock node covering the screen or a specific viewport.
		//   This is often used with ImGuiDockNodeFlags_PassthruCentralNode.
		// - Important: Dockspaces need to be submitted _before_ any window they can host. Submit it early in your frame! (*)
		// - Important: Dockspaces need to be kept alive if hidden, otherwise windows docked into it will be undocked.
		//   e.g. if you have multiple tabs with a dockspace inside each tab: submit the non-visible dockspaces with ImGuiDockNodeFlags_KeepAliveOnly.
		// (*) because of this constraint, the implicit \"Debug\" window can not be docked into an explicit DockSpace() node,
		// because that window is submitted as part of the part of the NewFrame() call. An easy workaround is that you can create
		// your own implicit "Debug##2" window after calling DockSpace() and leave it in the window stack for anyone to use.
		//void ShowExampleAppDockSpace(bool* p_open)
		//{
			// If you strip some features of, this demo is pretty much equivalent to calling DockSpaceOverViewport()!
			// In most cases you should be able to just call DockSpaceOverViewport() and ignore all the code below!
			// In this specific demo, we are not using DockSpaceOverViewport() because:
			// - we allow the host window to be floating/moveable instead of filling the viewport (when opt_fullscreen == false)
			// - we allow the host window to have padding (when opt_padding == true)
			// - we have a local menu bar in the host window (vs. you could use BeginMainMenuBar() + DockSpaceOverViewport() in your code!)
			// TL;DR; this demo is more complicated than what you would normally use.
			// If we removed all the options we are showcasing, this demo would become:
			//     void ShowExampleAppDockSpace()
			//     {
			//         ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
			//     }

		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.0f, 8.0f));
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 8.0f));
		
		window_flags |= ImGuiWindowFlags_NoTitleBar;
		window_flags |= ImGuiWindowFlags_NoCollapse;
		window_flags |= ImGuiWindowFlags_NoResize;
		window_flags |= ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
		window_flags |= ImGuiWindowFlags_NoNavFocus;

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
		// and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", nullptr, window_flags);
		ImGui::PopStyleVar(5);
		//ImGui::PopStyleVar(2);

		//ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8.0f, 8.0f));

		//Submit the DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}
	}

	void WindowEditor::setDockSpaceEnd()
	{
		
		ImGui::End();
		//ImGui::PopStyleVar();
	}

	void WindowEditor::setupMenuBar()
	{
		//if (ImGui::BeginMainMenuBar())
		
		//ImGuiStyle& style = ImGui::GetStyle();

		//static ImVec2 aa = style.FramePadding;
		//style.FramePadding = ImVec2(8.0f, 8.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2.0f, 8.0f));
		if (ImGui::BeginMenuBar())
		{
			ImGui::Button(ICON_FA_DOG, ImVec2(32, 32)); ImGui::SameLine();
			//ImGui::Button(ICON_FA_DNA, ImVec2(32, 32)); ImGui::SameLine();
			if (ImGui::BeginMenu("Examples"))
			{
				ImGui::MenuItem("Fullscreen", NULL);
				ImGui::MenuItem("Padding", NULL);
				ImGui::MenuItem("ShowDemo", NULL, &show_demo);
				ImGui::EndMenu();
			}
			//ImGui::PopStyleVar();
		}
		ImGui::PopStyleVar();
		//ImGui::EndMainMenuBar();
		ImGui::EndMenuBar();
		//style.FramePadding = aa;
		
	}

	// void WindowEditor::update()
	// {
    //     m_canvas->draw();
	// }

	void WindowEditor::handleCloseEvent()
	{
		//std::cout << "window is closed...." << std::endl;
	}
}