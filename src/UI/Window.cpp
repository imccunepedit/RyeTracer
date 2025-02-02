#include "UI/Window.h"

#include <stdlib.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"


using namespace Rye::UI;

void Window::Run()
{

    while (!glfwWindowShouldClose(windowHandle) && !shouldQuit)
    {
        // tell glfw to look for events
        glfwPollEvents();

        // tell opengl what color to make the rendered buffer
        glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode); // do the docking things, make sure whats rendered in the background can still be seen

        Update();

        // show a menu bar, useful for demo window and quitting the application
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("Menu"))
            {
                ImGui::MenuItem("Demo Window", NULL, &showDemoWindow);
                ImGui::ColorEdit4("Background (Clear) color", (float*) &clearColor, ImGuiColorEditFlags_NoInputs);
                ImGui::MenuItem("Quit", NULL, &shouldQuit);
                ImGui::EndMenu();
            }

            AppMenu();
            ImGui::EndMainMenuBar();
        }

        // show the demo window, very useful
        if (showDemoWindow)
            ImGui::ShowDemoWindow();


        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // swap the currently displayed buffer with the one that was just rendered
        glfwSwapBuffers(windowHandle);
    }

}


Window::Window()
{

    // initiallize glfw and check
    if (!glfwInit())
        std::exit(1);

    // tell glfw what opengl we are using
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create a window size x,y,title,not full screen
    windowHandle = glfwCreateWindow(1800, 900, "m_floating Renderer", nullptr, nullptr);


    // make sure window exists
    if (windowHandle == nullptr)
        std::exit(2);

    // tell glfw that we want to use our window
    glfwMakeContextCurrent(windowHandle);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        std::exit(3);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(windowHandle, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}


Window::~Window() {

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // tell glfw to kill our window and kill its self
    glfwDestroyWindow(windowHandle);
    glfwTerminate();
}
