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

	void Update() const;
	bool ShouldClose() const;

private:
	WindowInfo m_info{};
	GLFWwindow* m_window = nullptr;
};
