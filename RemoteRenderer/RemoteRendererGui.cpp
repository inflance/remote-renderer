#include "RemoteRendererGui.h"

#include <imgui.h>

#include "Application/Log.h"
#include "Window/Window.h"

RemoteRendererGui::RemoteRendererGui(Window* window): ImguiLayer(window)
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

	{
		ImGui::BeginMainMenuBar();
		if(ImGui::BeginMenu("Menu"))
		{
			if (ImGui::MenuItem("Pause"))
			{
				HandelPause();
			}

			if (ImGui::MenuItem("Exit"))
			{
				HandelExit();
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
	{
		ImGui::SetNextWindowPos(ImVec2(0, 30));

		ImGui::Begin("FPS");

		// 在每一帧更新帧率的值
		static float fps = 0.0f;
		fps = ImGui::GetIO().Framerate;

		// 显示帧率的值
		ImGui::Text("FPS: %.1f", fps);

		ImGui::End();

	}
	{
		ImGui::Begin("CameraMatrix");

		ImGui::End();
	}
	End();
}

bool RemoteRendererGui::Event()
{
	return ImguiLayer::Event();
}

void RemoteRendererGui::HandelPause()
{
}

void RemoteRendererGui::HandelExit() const
{
	Log::Instance().Info("Exit Remote Renderer app.");
	m_window->Close();
}
