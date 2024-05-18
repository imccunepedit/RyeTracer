#include "App.h"
#include "Camera.h"
#include "Image.h"
#include "imgui.h"
#include <cstdint>

#include "glm/gtc/type_ptr.hpp"


#define DEFAULT_WINDOW_WIDTH 1280
#define DEFUALT_WINDOW_HEIGHT 720


void App::Update() {

    // window containing our rendered image
    // remove padding
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f,0.0f));
    // 24 (8+16) remove scrollbars and scrolling
    ImGui::Begin("Viewport", NULL, 24);
    // keep track of the window size
    viewport_width = ImGui::GetContentRegionAvail().x;
    viewport_height = ImGui::GetContentRegionAvail().y;
    // draw the image into the viewport
    ImGui::Image((void*)(intptr_t)image->texture, ImVec2(image->width, image->height));
    ImGui::End();
    ImGui::PopStyleVar();


    ImGui::Begin("Controls");
    ImGui::Separator();
    ImGui::ColorEdit4("Background", (float*)&clear_color);
    ImGui::Checkbox("Show demo window: ", &show_demo_window);

    ImGui::Separator();
    if (ImGui::Button("Render"))
    {
        image->width = viewport_width;
        image->height = viewport_height;
        cam.render();
    }

    ImGui::Separator();
    ImGui::ColorEdit4("Sky color: ", glm::value_ptr(cam.sky_color));

    ImGui::Separator();
    ImGui::Text("image pointer = %x", image->texture);
    ImGui::Text("viewport size = %d x %d", image->width, image->height);
    ImGui::Text("fram time: %f", ImGui::GetIO().DeltaTime);



    ImGui::End();

    if (show_demo_window) ImGui::ShowDemoWindow();

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
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode); // do the docking things, make sure whats rendered in the background can still be seen

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
    window = glfwCreateWindow(DEFAULT_WINDOW_WIDTH, DEFUALT_WINDOW_HEIGHT, "m_floating Hello windows", nullptr, nullptr);

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

    cam.set_output(image);

}


App::~App() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // tell glfw to kill our window and kill its self
    glfwDestroyWindow(window);
    glfwTerminate();
}
