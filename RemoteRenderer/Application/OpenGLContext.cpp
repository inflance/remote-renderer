#include "OpenGLContext.h"

#include <iostream>
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

	// Create and compile shaders
	GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
	GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

	// Link shaders into a program
	m_shaderProgram = LinkShaders(vertexShader, fragmentShader);

	// Set up vertex data (a simple colored triangle)
	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // Vertex 1: Position (-0.5, -0.5), Color (Red)
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // Vertex 2: Position (0.5, -0.5), Color (Green)
		0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f   // Vertex 3: Position (0.0, 0.5), Color (Blue)
	};

	// Generate and bind a vertex array object (VAO)
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	// Generate and bind a vertex buffer object (VBO)
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	// Copy vertex data to the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Set the vertex attribute pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// Unbind the VAO and VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void OpenGLContext::Update()
{
	glClear(GL_COLOR_BUFFER_BIT);

	// Use the shader program
	glUseProgram(m_shaderProgram);

	// Bind the VAO
	glBindVertexArray(m_VAO);

	// Draw the triangle
	glDrawArrays(GL_TRIANGLES, 0, 3);

	// Unbind the VAO
	glBindVertexArray(0);
}

void OpenGLContext::Shutdown()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteProgram(m_shaderProgram);
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

GLuint OpenGLContext::CompileShader(GLenum shaderType, const char* source)
{
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	// Check for compilation errors
	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cerr << "Shader compilation error:\n" << infoLog << std::endl;
		glDeleteShader(shader);
		return 0;
	}

	return shader;
}

GLuint OpenGLContext::LinkShaders(GLuint vertexShader, GLuint fragmentShader)
{
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// Check for linking errors
	GLint success;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cerr << "Shader program linking error:\n" << infoLog << std::endl;
		glDeleteProgram(shaderProgram);
		return 0;
	}

	// Delete the individual shaders as they are now linked into the program
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}
