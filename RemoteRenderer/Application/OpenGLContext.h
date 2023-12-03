#pragma once

#include "glm/glm.hpp"

struct RenderData
{
	glm::vec4 clear_color{};
	int x{}, y{};
	int width{}, height{};
};

class OpenGLContext
{
public:
	explicit OpenGLContext(const RenderData& render_data);

	void Init();

	void Update();
	
	void Shutdown();

	void Resize(int x, int y, int width, int height);

	void SetClearColor(const glm::vec4& clear_color);

private:
	RenderData m_render_data{};
};
