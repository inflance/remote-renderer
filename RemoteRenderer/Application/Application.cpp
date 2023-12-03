﻿#include "Application.h"

#include "ImguiLayer.h"
#include "Layer.h"

void Application::Init()
{
	WindowInfo info{"RemoteRendererApp", 1280, 960};
	m_window = std::make_unique<Window>(info);

	m_window->Init();

	RenderData render_data{ {}, 0 , 0, m_window->Width(), m_window->Height() };
	m_gl_context = std::make_unique<OpenGLContext>(render_data);

	m_gl_context->Init();

	AddTopLayer(new ImguiLayer(m_window.get()));

	for (Layer* layer : m_layer_stack)
	{
		layer->Init();
	}
}

void Application::Shutdown()
{
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
	while (!m_window->ShouldClose())
	{
		m_window->PollEvents();

		m_gl_context->Update();
		for (Layer* layer : m_layer_stack)
		{
			constexpr float delta_time{};
			layer->Update(delta_time);
		}

		{
			int width, height;
			m_window->FrameBufferSize(width, height);
			m_gl_context->Resize(0, 0, width, height);
		}
		
		m_window->Update();
	}
}

void Application::AddLayer(Layer* layer)
{
	m_layer_stack.push_back(layer);
}

void Application::AddTopLayer(Layer* layer)
{
	m_layer_stack.push_front(layer);
}

void Application::AddButtonLayer(Layer* layer)
{
	m_layer_stack.push_back(layer);
}
