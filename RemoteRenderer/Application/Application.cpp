#include "Application.h"


void Application::Init()
{
	WindowInfo info{"RemoteRendererApp", 1280, 960};
	m_window = std::make_unique<Window>(info);

	m_window->Init();
}

void Application::Shutdown()
{
	m_window->Destroy();
	m_window.release();
}

void Application::Run()
{
	while (!m_window->ShouldClose())
	{
		m_window->Update();
	}
}
