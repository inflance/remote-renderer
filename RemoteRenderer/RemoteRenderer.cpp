
#include "RemoteRenderer.h"

#include "../build/RemoteRenderer/RemoteRendererGui.h"
#include "Application/Application.h"
#include "Application/ImguiLayer.h"
#include "Application/Log.h"

using namespace std;

int main()
{
    Log::Instance().Init();
    Application::Instance().Init();
    Application::Instance().AddTopLayer(new RemoteRendererGui(Application::Instance().GetWindow()));
    Application::Instance().Run();
    Application::Instance().Shutdown();
    Log::Instance().Shutdown();
	return 0;
}
