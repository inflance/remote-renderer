#include "RemoteRendererGui.h"

#include <imgui.h>
#include <memory>

#include "Application/Application.h"
#include "Application/CameraController.h"
#include "Application/Log.h"
#include "Application/MousePanCameraController.h"
#include "Window/Window.h"

RemoteRendererGui::RemoteRendererGui(): ImguiLayer()
{
	const auto height = Application::Instance().GetWindow()->Height();
	const auto width = Application::Instance().GetWindow()->Width();
	m_camera_controller = std::make_shared<MousePanCameraController>(
		Camera::CreateByPerspective(30.0, static_cast<float>(width) / static_cast<float>(height), 0.001f, 1000.0f));
	m_camera_controller->SetCameraPosition(glm::vec3(0, 0, 1));
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
	m_camera_controller->Update(delta_time);
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

void RemoteRendererGui::OnKeyReleasedEvent(const KeyReleasedEvent* event)
{
	Layer::OnKeyReleasedEvent(event);
}

void RemoteRendererGui::OnKeyPressedEvent(const KeyPressedEvent* event)
{
	Layer::OnKeyPressedEvent(event);
}

void RemoteRendererGui::OnAppClosedEvent(const AppLaunchedEvent* event)
{
	Layer::OnAppClosedEvent(event);
}

void RemoteRendererGui::OnAppLaunchedEvent(const AppLaunchedEvent* event)
{
	Layer::OnAppLaunchedEvent(event);
}

void RemoteRendererGui::OnMouseScrolledEvent(const MouseScrolledEvent* event)
{
	Layer::OnMouseScrolledEvent(event);
}

void RemoteRendererGui::OnMouseButtonReleasedEvent(const MouseButtonReleasedEvent* event)
{
	Layer::OnMouseButtonReleasedEvent(event);
}

void RemoteRendererGui::OnMouseButtonPressedEvent(const MouseButtonPressedEvent* event)
{
	Layer::OnMouseButtonPressedEvent(event);
}

void RemoteRendererGui::OnMouseMovedEvent(const MouseMovedEvent* event)
{
	Layer::OnMouseMovedEvent(event);
}

void RemoteRendererGui::OnWindowResizedEvent(const WindowResizedEvent* event)
{
	Layer::OnWindowResizedEvent(event);
}

void RemoteRendererGui::OnWindowClosedEvent(const WindowClosedEvent* event)
{
	Layer::OnWindowClosedEvent(event);
}
