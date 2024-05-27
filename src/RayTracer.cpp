#include "RayTracer.h"

#include <memory>
#include <cstdint>

#include "glm/gtc/type_ptr.hpp"

#include "Camera.h"
#include "Image.h"
#include "imgui.h"
#include "Scene.h"
#include "Sphere.h"



RayTracer::RayTracer ()
{
    image = new Image();
    my_scene.load_default();
    cam.initialize(image);
}

RayTracer::~RayTracer()
{
    delete(image);
}

void RayTracer::app_menu()
{
    if (ImGui::BeginMenu("Info"))
    {
        ImGui::MenuItem("camera debug", NULL, &show_camera_debug);
        ImGui::EndMenu();
    }
}

void RayTracer::Update()
{
    ImGuiIO& io = ImGui::GetIO();

    cam.resize();
    // cam.calculate_projection();


    cam.move(window_handle, io.DeltaTime);

    if (show_camera_debug)
        cam.debug_window();

    ImGui::Begin("Controls");
    ImGui::SeparatorText("Info");
    ImGui::Text("Viewport size: %d x %d", image->width, image->height);
    ImGui::Text("Frame time (fps): %.2fms (%.1f)", io.DeltaTime*1000, 1/io.DeltaTime);

    ImGui::SeparatorText("Camera");
    ImGui::DragFloat3("Position", glm::value_ptr(cam.position), 0.1f);
    ImGui::DragFloat3("Look direction", glm::value_ptr(cam.forward), 0.1f);
    // ImGui::DragFloat3("Look point", glm::value_ptr(cam.look_point), 0.1f);
    ImGui::DragFloat("Focal Distance", &cam.focal_dist, 0.1f);
    if (ImGui::Button("Render"))
    {
        cam.render(my_scene);
        // std::thread render_thread(&Camera::render, &cam, my_scene, image);
        // render_thread.join();
    }
    ImGui::SameLine();
    ImGui::Checkbox("render every frame", &render_every_frame);
    if (render_every_frame) {
        cam.render(my_scene);
    }

    if (ImGui::Button("Reset accumulator"))
        cam.reset_accumulator();

    ImGui::End();


    ImGui::Begin("Scene");
    ImGui::ColorEdit3("Sky color", glm::value_ptr(my_scene.sky_material.emissive), ImGuiColorEditFlags_Float);
    ImGui::ColorEdit3("Directional Light color", glm::value_ptr(my_scene.directional_light_color), ImGuiColorEditFlags_Float);
    ImGui::DragFloat3("Directional Light direction", glm::value_ptr(my_scene.directional_light_direction), 0.1f, -1.0f, 1.0f);
    if (ImGui::Button("Add Sphere")) {
        my_scene.add_sphere(Sphere({10,0,0},1,Material()));;
    }
    ImGui::SetNextItemOpen(true, ImGuiCond_Once);
    if (ImGui::TreeNode("Spheres"))
    {
        for (int i = 0; i < my_scene.spheres.size(); i++)
        {
            ImGui::SetNextItemOpen(true, ImGuiCond_Once);
            if (ImGui::TreeNode((void*)(intptr_t)i, "Sphere %d", i))
            {
                ImGui::ColorEdit3("Color", glm::value_ptr(my_scene.spheres[i].material.diffuse), ImGuiColorEditFlags_Float);
                ImGui::DragFloat("Roughnes", &my_scene.spheres[i].material.roughness, 0.001f, 0.0f, 1.0f);
                ImGui::ColorEdit3("Emission", glm::value_ptr(my_scene.spheres[i].material.emissive), ImGuiColorEditFlags_Float);
                ImGui::DragFloat("Strength", &my_scene.spheres[i].material.emissive_strength, 0.1f, 0.0f);
                ImGui::DragFloat3("Position", glm::value_ptr(my_scene.spheres[i].center), 0.1f);
                ImGui::DragFloat("radius", &my_scene.spheres[i].radius, 0.1f);
                if (ImGui::Button("Remove"))
                {
                    my_scene.remove_sphere(i);
                }
                ImGui::TreePop();
            }
        }
        ImGui::TreePop();
    }

    ImGui::End();

    // draw our rendered image to the viewport
    image->draw_image();

};
