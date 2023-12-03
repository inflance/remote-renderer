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

private:
	std::unique_ptr<Window> m_window = nullptr;
	std::unique_ptr<OpenGLContext> m_gl_context = nullptr;
	std::deque<Layer*> m_layer_stack;
};
