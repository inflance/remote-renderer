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
	Log::Instance().Debug(event->ToString());
	for (Layer* layer : m_layer_stack)
	{
		layer->OnEvent(event);
	}
	if (event->GetType() & Event::EventType::WindowEvent)
	{
		OnWindowEvent(dynamic_cast<const WindowEvent*>(event));
	}
}

void Application::OnWindowEvent(const WindowEvent* event)
{
	if (event->GetWindowEventType() == WindowEvent::WindowResized)
	{
		OnWindowResizedEvent(dynamic_cast<const WindowResizedEvent*>(event));
	}
	if (event->GetWindowEventType() == WindowEvent::WindowClosed)
	{
		OnWindowClosedEvent(dynamic_cast<const WindowClosedEvent*>(event));
	}
}

void Application::OnWindowResizedEvent(const WindowResizedEvent* event)
{
	Log::Instance().Debug(event->ToString());
	m_gl_context->Resize(0, 0, event->GetWidth(), event->GetHeight());
}

void Application::OnWindowClosedEvent(const WindowClosedEvent* event)
{
	Log::Instance().Debug(event->ToString());
	m_close = true;
}
