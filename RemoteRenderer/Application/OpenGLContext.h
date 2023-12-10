#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

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
    GLuint m_VAO, m_VBO, m_shaderProgram;

    // Shader source code
    const char* vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 position;
        layout (location = 1) in vec3 color;
        out vec3 fragColor;
        void main()
        {
            gl_Position = vec4(position, 1.0);
            fragColor = color;
        }
    )";

    const char* fragmentShaderSource = R"(
        #version 330 core
        in vec3 fragColor;
        out vec4 finalColor;
        void main()
        {
            finalColor = vec4(fragColor, 1.0);
        }
    )";

    GLuint CompileShader(GLenum shaderType, const char* source);

	GLuint LinkShaders(GLuint vertexShader, GLuint fragmentShader);
};
