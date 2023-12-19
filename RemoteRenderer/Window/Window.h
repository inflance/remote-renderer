#pragma once

#include <string>
#include <GLFW/glfw3.h>

#include "Application/EventDispatcher.h"

struct WindowInfo
{
	std::string title{};
	int width = 0, height = 0;
};

class Window
{
public:
	using Callback = std::function<void(const Event*)>;

	explicit Window(WindowInfo window_info);

	void Init();
	static void Destroy();

	void SetEventCallback(Callback&& callback) ;
	void Close() ;
	static void SetVSync(int i);
	[[nodiscard]] int Width() const { return m_info.width; }
	[[nodiscard]] int Height() const { return m_info.height; }

	static void PollEvents();

	void Update() const;
	bool IsMouseButtonPressed(int button) const;
	bool IsMouseButtonReleased(int button) const;

	[[nodiscard]] bool ShouldClose() const;

	[[nodiscard]] GLFWwindow* Get() const { return m_window; }

	void FrameBufferSize(int& width, int& height) const;
	void WindowScale(float& width_scale, float& height_scale) const;
	void GetMousePos(double& x_pos, double& y_pos);

	EventDispatcher& GetDispatcher() { return m_dispatcher; }

private:
	WindowInfo m_info{};
	EventDispatcher m_dispatcher{};
	GLFWwindow* m_window = nullptr;
	std::thread m_handle_thread;
};
