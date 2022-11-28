#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx12.h"
#include <d3d12.h>
#include <dxgi1_4.h>
#include "RenderDevice.h"


namespace TARDIS::UI
{
	class DirectX12Device : public RenderDevice
	{
	public:
		DirectX12Device();

		~DirectX12Device();

		void initWindow() override;

		void render() override;

		bool isRunning() override;

	private:
		HWND m_hwnd;
		WNDCLASSEX wc;
		static ImVec4 clear_color;
		bool done = false;
	};
}