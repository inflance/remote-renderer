#include "Window.h"

#include <memory>

#include "../Application/Log.h"
#include "Application/EventDispatcher.h"

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

	m_handle_thread = std::thread([this]() { m_dispatcher.ProcessEvents(); });
	m_handle_thread.detach();
}

void Window::Destroy()
{
	glfwTerminate();
}

void Window::SetEventCallback(Callback&& callback)
{
	glfwSetWindowUserPointer(m_window, this);
	m_dispatcher.AddEventListener(callback);

	glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
	{
		auto* data = static_cast<Window*>(glfwGetWindowUserPointer(window));

		if (data != nullptr)
		{
			data->GetDispatcher().EnqueueEvent(std::make_shared<WindowClosedEvent>());
		}
	});

	glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
	{
		auto* data = static_cast<Window*>(glfwGetWindowUserPointer(window));

		if (data != nullptr)
		{
			data->GetDispatcher().EnqueueEvent(std::make_shared<WindowResizedEvent>(width, height));
		}
	});

	glfwSetWindowContentScaleCallback(m_window, [](GLFWwindow* window, float x_scale, float y_scale)
	{
		auto* data = static_cast<Window*>(glfwGetWindowUserPointer(window));

		if (data != nullptr)
		{
			data->GetDispatcher().EnqueueEvent(std::make_shared<WindowScaledEvent>(x_scale, y_scale));
		}
	});

	glfwSetWindowFocusCallback(m_window, [](GLFWwindow* window, int focused)
	{
		auto* data = static_cast<Window*>(glfwGetWindowUserPointer(window));

		if (data != nullptr)
		{
			data->GetDispatcher().EnqueueEvent(std::make_shared<WindowFocusedEvent>(focused));
		}
	});

	glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods)
	{
		auto* data = static_cast<Window*>(glfwGetWindowUserPointer(window));

		if (data != nullptr)
		{
			if (action == GLFW_PRESS)
			{
				data->GetDispatcher().EnqueueEvent(std::make_shared<MouseButtonPressedEvent>(button, mods));
			}
			else if (action == GLFW_RELEASE)
			{
				data->GetDispatcher().EnqueueEvent(std::make_shared<MouseButtonReleasedEvent>(button, mods));
			}
		}
	});

	glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xpos, double ypos)
	{
		auto* data = static_cast<Window*>(glfwGetWindowUserPointer(window));

		if (data != nullptr)
		{
			data->GetDispatcher().EnqueueEvent(std::make_shared<MouseMovedEvent>(xpos, ypos));
		}
	});

	glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scan_code, int action, int mods)
	{
		auto* data = static_cast<Window*>(glfwGetWindowUserPointer(window));

		if (data != nullptr)
		{
			if (action == GLFW_PRESS)
			{
				data->GetDispatcher().EnqueueEvent(std::make_shared<KeyPressedEvent>(key, mods));
			}
			else if (action == GLFW_RELEASE)
			{
				data->GetDispatcher().EnqueueEvent(std::make_shared<MouseButtonReleasedEvent>(key, mods));
			}
		}
	});
}

void Window::Close() 
{
	GetDispatcher().EnqueueEvent(std::make_shared<WindowClosedEvent>());
}

void Window::SetVSync(int i)
{
	glfwSwapInterval(i);
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

void Window::WindowScale(float& width_scale, float& height_scale) const
{
	glfwGetWindowContentScale(m_window, &width_scale, &height_scale);
}
