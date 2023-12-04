#include "ImguiLayer.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Log.h"
#include "Window/Window.h"

ImguiLayer::ImguiLayer(Window* window)
	: Layer("ImguiLayer"), m_window(window)
{
}

ImguiLayer::~ImguiLayer()
{
}

void ImguiLayer::Init()
{
	IMGUI_CHECKVERSION();
	Log::Instance().Info("ImGui version: {} ", ImGui::GetVersion());
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; 
	float x_scale, y_scale;
	m_window->WindowScale(x_scale, y_scale);
	io.DisplayFramebufferScale = ImVec2(x_scale, y_scale);
	io.FontGlobalScale = (x_scale + y_scale) / 2;

	ImGui_ImplGlfw_InitForOpenGL(m_window->Get(), true);
	ImGui_ImplOpenGL3_Init("#version 330 core");
}

void ImguiLayer::Shutdown()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void ImguiLayer::Begin()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void ImguiLayer::End()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImguiLayer::Update(float delta_time)
{
	Begin();

	ImGui::ShowDemoWindow(&show_demo_window);

	End();
}

bool ImguiLayer::Event()
{
	return Layer::Event();
}
