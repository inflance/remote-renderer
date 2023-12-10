#pragma once

#include "Application/ImguiLayer.h"

class CameraController;

class RemoteRendererGui final : public ImguiLayer
{
public:
	RemoteRendererGui();

	~RemoteRendererGui() override;
	void Init() override;
	void Shutdown() override;
	void Update(float delta_time) override;

	void ShowMenuBar();
	static void ShowFpsWindow();
	void HandelPause();
	static void HandelExit();
	static void HandelVSync();

	void OnKeyReleasedEvent(const KeyReleasedEvent* event) override;
	void OnKeyPressedEvent(const KeyPressedEvent* event) override;
	void OnAppClosedEvent(const AppLaunchedEvent* event) override;
	void OnAppLaunchedEvent(const AppLaunchedEvent* event) override;
	void OnMouseScrolledEvent(const MouseScrolledEvent* event) override;
	void OnMouseButtonReleasedEvent(const MouseButtonReleasedEvent* event) override;
	void OnMouseButtonPressedEvent(const MouseButtonPressedEvent* event) override;
	void OnMouseMovedEvent(const MouseMovedEvent* event) override;
	void OnWindowResizedEvent(const WindowResizedEvent* event) override;
	void OnWindowClosedEvent(const WindowClosedEvent* event) override;
private:
	std::shared_ptr<CameraController> m_camera_controller;
};
