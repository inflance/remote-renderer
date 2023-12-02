
#include "RemoteRenderer.h"

#include "Application/Application.h"
#include "Application/Log.h"

using namespace std;

int main()
{
    Log::Instance().Init();
    Application::Instance().Init();
    Application::Instance().Run();
    Application::Instance().Shutdown();
    Log::Instance().Shutdown();
	return 0;
}
