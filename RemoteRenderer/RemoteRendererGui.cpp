#include "RemoteRendererGui.h"

#include <imgui.h>

#include "Application/Application.h"
#include "Application/Log.h"
#include "Window/Window.h"

RemoteRendererGui::RemoteRendererGui(): ImguiLayer()
{
}

RemoteRendererGui::~RemoteRendererGui()
{
}

void RemoteRendererGui::Init()
{
	ImguiLayer::Init();
}

void RemoteRendererGui::Shutdown()
{
	ImguiLayer::Shutdown();
}

void RemoteRendererGui::Update(float delta_time)
{
	Begin();

	ShowMenuBar();

	ShowFpsWindow();

	{
		ImGui::Begin("CameraMatrix");

		ImGui::End();
	}
	End();
}

void RemoteRendererGui::ShowMenuBar()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("Menu"))
		{
			if (ImGui::MenuItem("Pause"))
			{
				HandelPause();
			}

			if (ImGui::MenuItem("SetVSync"))
			{
				HandelVSync();
			}

			if (ImGui::MenuItem("Exit"))
			{
				HandelExit();
			}

			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}

void RemoteRendererGui::ShowFpsWindow()
{
	ImGui::SetNextWindowPos(ImVec2(0, 30));

	if (ImGui::Begin("FPS"))
	{
		static float fps = 0.0f;
		fps = ImGui::GetIO().Framerate;

		ImGui::Text("FPS: %.1f", fps);

		ImGui::End();
	}
}

void RemoteRendererGui::HandelPause()
{
}

void RemoteRendererGui::HandelExit()
{
	Log::Instance().Info("Exit Remote Renderer app.");
	Application::Instance().GetWindow()->Close();
}

void RemoteRendererGui::HandelVSync()
{
	Window::SetVSync(1);
}
