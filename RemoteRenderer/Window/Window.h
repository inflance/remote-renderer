#pragma once

#include <string>
#include <GLFW/glfw3.h>

struct WindowInfo
{
	std::string title{};
	int width = 0, height = 0;
};

class Window
{
public:
	explicit Window(WindowInfo window_info);

	void Init();
	static void Destroy();

	[[nodiscard]] int Width() const { return m_info.width; }
	[[nodiscard]] int Height() const { return m_info.height; }

	static void PollEvents();

	void Update() const;

	[[nodiscard]] bool ShouldClose() const;

	[[nodiscard]] GLFWwindow* Get() const { return m_window; }

	void FrameBufferSize(int& width, int& height) const;

private:
	WindowInfo m_info{};
	GLFWwindow* m_window = nullptr;
};
