#include <memory>
#include <cstdint>

#include "glm/gtc/type_ptr.hpp"

#include "App.h"
#include "Camera.h"
#include "Image.h"
#include "imgui.h"
#include "Scene.h"
#include "Sphere.h"



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
    ImGui::SeparatorText("ImGui");
    ImGui::ColorEdit4("Background", (float*)&clear_color);
    ImGui::Checkbox("Show demo window: ", &show_demo_window);

    ImGui::SeparatorText("Camera");
    ImGui::DragFloat3("Position", glm::value_ptr(cam.position));
    ImGui::DragFloat3("Look direction", glm::value_ptr(cam.forward));
    ImGui::DragFloat("Focal Distance", &cam.focal_dist);
    if (ImGui::Button("Render"))
    {
        image->width = viewport_width;
        image->height = viewport_height;
        cam.render(my_scene, image);
    }
    ImGui::SameLine();
    ImGui::Checkbox("render every frame", &render_every_frame);
    if (render_every_frame) {
        image->width = viewport_width;
        image->height = viewport_height;
        cam.render(my_scene, image);
    }



    ImGui::Text("viewport: %f, %f, %f", cam.viewport_origin.x, cam.viewport_origin.y, cam.viewport_origin.z);
    ImGui::Text("du: %f, %f, %f", cam.viewport_du.x, cam.viewport_du.y, cam.viewport_du.z);
    ImGui::Text("dv: %f, %f, %f", cam.viewport_dv.x, cam.viewport_dv.y, cam.viewport_dv.z);


    ImGui::SeparatorText("Image");
    ImGui::Text("Image pointer: 0x%x", image->texture);
    ImGui::Text("Viewport size: %d x %d", image->width, image->height);
    ImGui::Text("Frame time (fps): %fms (%f)", ImGui::GetIO().DeltaTime*1000, ImGui::GetIO().Framerate);

    ImGui::SeparatorText("Scene");
    ImGui::ColorEdit4("Sky color", glm::value_ptr(my_scene.sky_color), ImGuiColorEditFlags_Float);
    if (ImGui::Button("Add Sphere")) {
        my_scene.add_sphere(Sphere({10,0,0},1,{1,0,0,1}));;
    }
    ImGui::Spacing();
    if (ImGui::TreeNode("Spheres")) {
        for (int i = 0; i < my_scene.spheres.size(); i++) {
            ImGui::SetNextItemOpen(true, ImGuiCond_Once);
            if (ImGui::TreeNode((void*)(intptr_t)i, "Sphere %d", i)) {
                ImGui::ColorEdit4("Color", glm::value_ptr(my_scene.spheres[i].color));
                ImGui::DragFloat3("Position", glm::value_ptr(my_scene.spheres[i].center));
                if (ImGui::Button("Remove")) {
                    my_scene.spheres.erase(std::next(my_scene.spheres.begin(), i));
                }
                ImGui::TreePop();
            }
        }
        ImGui::TreePop();
    }

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



    my_scene.add_sphere(Sphere(glm::vec3(4,0,0), 1, glm::vec4(0,1,0,1)));
    my_scene.add_sphere(Sphere(glm::vec3(4,2,0), 1, glm::vec4(1,0,0,1)));
    my_scene.add_sphere(Sphere(glm::vec3(4,-2,0), 1, glm::vec4(1,1,0,1)));
}


App::~App() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // tell glfw to kill our window and kill its self
    glfwDestroyWindow(window);
    glfwTerminate();
}
