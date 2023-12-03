#include "Window.h"

#include "../Application/Log.h"

Window::Window(WindowInfo window_info)
	: m_info(std::move(window_info))
{
}

void Window::Init()
{
	if (!glfwInit())
	{
		Log::Instance().Error("Could not init GLFW window!");
	}
	int major, minor, rev;
	glfwGetVersion(&major, &minor, &rev);
	Log::Instance().Info("Create GLFW Window, Version:{}.{}.{}", major, minor, rev);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(m_info.width, m_info.height, m_info.title.c_str(), nullptr, nullptr);
	if (!m_window)
	{
		glfwTerminate();
		Log::Instance().Error("Could not create GLFW window!");
	}

	glfwMakeContextCurrent(m_window);
}

void Window::Destroy()
{
	glfwTerminate();
}

void Window::PollEvents()
{
	glfwPollEvents();
}

void Window::Update() const
{
	glfwSwapBuffers(m_window);
}

bool Window::ShouldClose() const
{
	return glfwWindowShouldClose(m_window);
}

void Window::FrameBufferSize(int& width, int& height) const
{
	glfwGetFramebufferSize(m_window, &width, &height);
}
