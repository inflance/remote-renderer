#pragma once

#include <deque>
#include <memory>

#include "OpenGLContext.h"
#include "Singleton.h"
#include "Window/Window.h"

class Layer;

class Application : public Singleton<Application>
{
public:
	void Init();
	void Shutdown();
	void Run();
	void AddLayer(Layer* layer);
	void AddTopLayer(Layer* layer);
	void AddButtonLayer(Layer* layer);

	[[nodiscard]] Window* GetWindow() const { return m_window.get(); }
	void OnEvent(const Event* event);
	void OnKeyEvent(const KeyEvent* event);
	void OnKeyReleasedEvent(const KeyReleasedEvent* event) const;
	void OnKeyPressedEvent(const KeyPressedEvent* event) const;
	void OnApplicationEvent(const ApplicationEvent* event);
	void OnAppClosedEvent(const AppLaunchedEvent* event) const;
	void OnAppLaunchedEvent(const AppLaunchedEvent* event);
	void OnMouseEvent(const MouseEvent* event);
	void OnMouseScrolledEvent(const MouseScrolledEvent* event);
	void OnMouseButtonReleasedEvent(const MouseButtonReleasedEvent* event);
	void OnMouseButtonPressedEvent(const MouseButtonPressedEvent* event);
	void OnMouseMovedEvent(const MouseMovedEvent* event);
	void OnWindowEvent(const WindowEvent* event);
	void OnWindowResizedEvent(const WindowResizedEvent* event);
	void OnWindowClosedEvent(const WindowClosedEvent* event);

private:
	std::unique_ptr<Window> m_window = nullptr;
	std::unique_ptr<OpenGLContext> m_gl_context = nullptr;
	std::deque<Layer*> m_layer_stack;
	bool m_close = false;
};
