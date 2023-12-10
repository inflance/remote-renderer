#include "Application.h"

#include "ImguiLayer.h"
#include "Layer.h"
#include "Log.h"

void Application::Init()
{
	WindowInfo info{"RemoteRendererApp", 1280, 960};
	m_window = std::make_unique<Window>(info);
	m_window->Init();
	m_window->SetEventCallback([this](auto&& PH1) { OnEvent(std::forward<decltype(PH1)>(PH1)); });
	m_window->GetDispatcher().EnqueueEvent(std::make_shared<AppLaunchedEvent>());

	RenderData render_data{{}, 0, 0, m_window->Width(), m_window->Height()};
	m_gl_context = std::make_unique<OpenGLContext>(render_data);
	m_gl_context->Init();
}

void Application::Shutdown()
{
	m_window->GetDispatcher().EnqueueEvent(std::make_shared<AppClosedEvent>());
	for (Layer* layer : m_layer_stack)
	{
		layer->Shutdown();
		delete layer;
		layer = nullptr;
	}
	m_gl_context->Shutdown();
	m_gl_context.release();

	m_window->Destroy();
	m_window.release();
}

void Application::Run()
{
	while (!m_close)
	{
		m_window->PollEvents();

		m_gl_context->Update();
		for (Layer* layer : m_layer_stack)
		{
			constexpr float delta_time{};
			layer->Update(delta_time);
		}
		m_window->Update();
	}
}

void Application::AddLayer(Layer* layer)
{
	m_layer_stack.push_back(layer);
	layer->Init();
}

void Application::AddTopLayer(Layer* layer)
{
	m_layer_stack.push_front(layer);
	layer->Init();
}

void Application::AddButtonLayer(Layer* layer)
{
	m_layer_stack.push_back(layer);
	layer->Init();
}

void Application::OnEvent(const Event* event)
{
	for (Layer* layer : m_layer_stack)
	{
		layer->OnEvent(event);
	}
	if (event->GetType() & Event::EventType::WindowEvent)
	{
		OnWindowEvent(dynamic_cast<const WindowEvent*>(event));
	}
	if (event->GetType() & Event::EventType::MouseEvent)
	{
		OnMouseEvent(dynamic_cast<const MouseEvent*>(event));
	}
	if (event->GetType() & Event::EventType::ApplicationEvent)
	{
		OnApplicationEvent(dynamic_cast<const ApplicationEvent*>(event));
	}
	if (event->GetType() & Event::EventType::KeyEvent)
	{
		OnKeyEvent(dynamic_cast<const KeyEvent*>(event));
	}
}

void Application::OnKeyEvent(const KeyEvent* event)
{
	switch (event->GetKeyEventType())
	{
	case KeyEvent::KeyPressed:
		OnKeyPressedEvent(dynamic_cast<const KeyPressedEvent*>(event));
		break;
	case KeyEvent::KeyReleased:
		OnKeyReleasedEvent(dynamic_cast<const KeyReleasedEvent*>(event));
		break;
	default: break;
	}
}

void Application::OnKeyReleasedEvent(const KeyReleasedEvent* event) const
{
	for (const auto layer : m_layer_stack)
	{
		layer->OnKeyReleasedEvent(event);
	}
}

void Application::OnKeyPressedEvent(const KeyPressedEvent* event) const
{
	for (const auto layer : m_layer_stack)
	{
		layer->OnKeyPressedEvent(event);
	}
}

void Application::OnApplicationEvent(const ApplicationEvent* event)
{
	switch (event->GetApplicationEventType()) {
	case ApplicationEvent::AppLaunched:
		OnAppLaunchedEvent(dynamic_cast<const AppLaunchedEvent*>(event));
		break;
	case ApplicationEvent::AppClosed:
		OnAppClosedEvent(dynamic_cast<const AppLaunchedEvent*>(event));
		break;
	default: ;
	}
}

void Application::OnAppClosedEvent(const AppLaunchedEvent* event) const
{
	for (const auto layer : m_layer_stack)
	{
		layer->OnAppClosedEvent(event);
	}
}

void Application::OnAppLaunchedEvent(const AppLaunchedEvent* event)
{
	for (const auto layer : m_layer_stack)
	{
		layer->OnAppLaunchedEvent(event);
	}
}

void Application::OnMouseEvent(const MouseEvent* event)
{
	switch (event->GetMouseEventType()) {
	case MouseEvent::MouseMoved:
		OnMouseMovedEvent(dynamic_cast<const MouseMovedEvent*>(event));
		break;
	case MouseEvent::MouseButtonPressed:
		OnMouseButtonPressedEvent(dynamic_cast<const MouseButtonPressedEvent*>(event));
		break;
	case MouseEvent::MouseButtonReleased:
		OnMouseButtonReleasedEvent(dynamic_cast<const MouseButtonReleasedEvent*>(event));
		break;
	case MouseEvent::MouseScrolled:
		OnMouseScrolledEvent(dynamic_cast<const MouseScrolledEvent*>(event));
		break;
	default: ;
	}
}

void Application::OnMouseScrolledEvent(const MouseScrolledEvent* event)
{
	for (const auto layer : m_layer_stack)
	{
		layer->OnMouseScrolledEvent(event);
	}
}

void Application::OnMouseButtonReleasedEvent(const MouseButtonReleasedEvent* event)
{
	for (const auto layer : m_layer_stack)
	{
		layer->OnMouseButtonReleasedEvent(event);
	}
}

void Application::OnMouseButtonPressedEvent(const MouseButtonPressedEvent* event)
{
	for (const auto layer : m_layer_stack)
	{
		layer->OnMouseButtonPressedEvent(event);
	}
}

void Application::OnMouseMovedEvent(const MouseMovedEvent* event)
{
	for (const auto layer : m_layer_stack)
	{
		layer->OnMouseMovedEvent(event);
	}
}

void Application::OnWindowEvent(const WindowEvent* event)
{
	if (event->GetWindowEventType() == WindowEvent::WindowResized)
	{
		OnWindowResizedEvent(dynamic_cast<const WindowResizedEvent*>(event));
	}
	else if (event->GetWindowEventType() == WindowEvent::WindowClosed)
	{
		OnWindowClosedEvent(dynamic_cast<const WindowClosedEvent*>(event));
	}
}

void Application::OnWindowResizedEvent(const WindowResizedEvent* event)
{
	Log::Instance().Debug(event->ToString());
	for (const auto layer : m_layer_stack)
	{
		layer->OnWindowResizedEvent(event);
	}
	
	m_gl_context->Resize(0, 0, event->GetWidth(), event->GetHeight());
}

void Application::OnWindowClosedEvent(const WindowClosedEvent* event)
{
	for (const auto layer : m_layer_stack)
	{
		layer->OnWindowClosedEvent(event);
	}
	Log::Instance().Debug(event->ToString());
	m_close = true;
}
