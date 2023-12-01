
#include "RemoteRenderer.h"
#include <imgui.h>
#include <GLFW/glfw3.h>

using namespace std;

int main()
{
    // 初始化GLFW
    if (!glfwInit()) {
        // 初始化失败
        return -1;
    }

    // 创建窗口
    GLFWwindow* window = glfwCreateWindow(800, 600, "My Window", nullptr, nullptr);
    if (!window) {
        // 创建窗口失败
        glfwTerminate();
        return -1;
    }

    // 设置当前上下文为窗口上下文
    glfwMakeContextCurrent(window);

    // 初始化Dear ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

   /* ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");*/

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        /*ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();*/
        ImGui::NewFrame();

        ImGui::Begin("My ImGui Window");
        ImGui::Text("Hello, world!");
        ImGui::End();

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        /*glViewport(0, 0, display_w, display_h);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);*/
        //ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    /*ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();*/
    ImGui::DestroyContext();

    glfwTerminate();

	return 0;
}
