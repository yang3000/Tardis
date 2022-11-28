#pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

namespace TARDIS::UI
{
	class RenderDevice
	{
	public:
		RenderDevice() {};

		virtual ~RenderDevice() {};

		virtual void initWindow() = 0;

		//virtual void preRender() = 0;

		virtual void render() = 0;

		//virtual void postRender() = 0;

		virtual bool isRunning() = 0;
	};
}