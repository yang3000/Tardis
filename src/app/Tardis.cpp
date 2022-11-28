#include "Tardis.h"

#include "Application.h"

using namespace TARDIS;

int main()
{
	UI::Application* app = new UI::Application();

	app->run();

	delete app;
    
	TDS_LOG_INFO("app is exited.");
}