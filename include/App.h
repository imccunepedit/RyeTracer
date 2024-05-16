#ifndef APP_H_
#define APP_H_

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "GLFW/glfw3.h"
#include <GL/gl.h>
#include <cstdio>
#include <stdlib.h>

class App {
public:
    App() {
        if (!glfwInit())
            std::exit(1);

        window = glfwCreateWindow(1280, 720, "m_floating Hello windows", nullptr, nullptr);

        if (window == nullptr)
            std::exit(1);

        glfwMakeContextCurrent(window);

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking

        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init();
    }

    ~App() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        glfwDestroyWindow(window);
        glfwTerminate();
    }


    void Run() {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
            ImGui_ImplGlfw_NewFrame();
            ImGui_ImplOpenGL3_NewFrame();
            ImGui::NewFrame();
            ImGui::DockSpaceOverViewport();

            Update();

            ImGui::Render();
            int display_w, display_h;
            glfwGetFramebufferSize(window, &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            glClearColor(clear_color.x*clear_color.w, clear_color.y*clear_color.w, clear_color.z*clear_color.w, clear_color.w);
            glClear(GL_COLOR_BUFFER_BIT);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            glfwSwapBuffers(window);
        }
    }


    void Update() {
        if (show_demo_window) ImGui::ShowDemoWindow();
    }



private:
    GLFWwindow* window;
    bool show_demo_window = true;
    ImVec4 clear_color = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);

};


#endif // APP_H_
