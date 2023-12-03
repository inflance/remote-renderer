#include "OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Log.h"

OpenGLContext::OpenGLContext(const RenderData& render_data)
	: m_render_data(render_data)
{
}

void OpenGLContext::Init()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		Log::Instance().Error("Failed to initialize glad!");
	}

	Log::Instance().Debug("OpenGL version: {}.{}", GLVersion.major, GLVersion.minor);
	SetClearColor(m_render_data.clear_color);
	Resize(m_render_data.x, m_render_data.y, m_render_data.width, m_render_data.height);
}

void OpenGLContext::Update()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLContext::Shutdown()
{
}

void OpenGLContext::Resize(int x, int y, int width, int height)
{
	m_render_data.x = x;
	m_render_data.y = y;
	m_render_data.width = width;
	m_render_data.height = height;
	glViewport(x, y, width, height);
}

void OpenGLContext::SetClearColor(const glm::vec4& clear_color)
{
	m_render_data.clear_color = clear_color;
	glClearColor(m_render_data.clear_color.x, m_render_data.clear_color.y, m_render_data.clear_color.z,
	             m_render_data.clear_color.w);
}
