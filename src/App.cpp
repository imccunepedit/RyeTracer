#include "App.h"
#include "Camera.h"
#include "imgui.h"
#include <cstdint>


void App::Update() {


    ImGui::Begin("Viewport");
    image_width = ImGui::GetContentRegionAvail().x;
    image_height = ImGui::GetContentRegionAvail().y;
    ImGui::Image((void*)(intptr_t)image_texture, ImVec2(image_width, image_height));
    ImGui::End();


    ImGui::Begin("Controls");
    ImGui::ColorEdit4("Background", (float*)&clear_color);

    if (ImGui::Button("Render"))
    {
        Camera cam;
        cam.Render(&image_texture, image_width, image_height);
    }

    ImGui::Text("image pointer = %x", image_texture);
    ImGui::Text("image size = %d x %d", image_width, image_height);
    ImGui::End();



}


void App::Run() {

    while (!glfwWindowShouldClose(window)) {
        // tell glfw to look for events
        glfwPollEvents();

        // int display_w, display_h;
        // glfwGetFramebufferSize(window, &display_w, &display_h);


        // tell opengl what color to make the rendered buffer
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplGlfw_NewFrame();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

        Update();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // swap the currently displayed buffer with the one that was just rendered
        glfwSwapBuffers(window);

    }

}

App::App() {

    // initiallize glfw and check
    if (!glfwInit())
        std::exit(1);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // create a window size x,y,title,fullscreen
    window = glfwCreateWindow(800, 800, "m_floating Hello windows", nullptr, nullptr);

    // make sure window exists
    if (window == nullptr)
        std::exit(1);


    // tell glfw that we want to use our window
    glfwMakeContextCurrent(window);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

}


App::~App() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // tell glfw to kill our window and kill its self
    glfwDestroyWindow(window);
    glfwTerminate();
}
