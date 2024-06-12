#include "RayTracer.h"

#include <memory>
#include <cstdint>
#include <iostream>

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
    cam.recalulate_all(image);
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

    cam.move(window_handle, io.DeltaTime);

    if (render_every_frame) {
        cam.render(my_scene);
    }
    if (show_camera_debug)
        cam.debug_window();

    ImGui::Begin("Controls");
    ImGui::SeparatorText("Info");
    ImGui::Text("Viewport size: %d x %d", image->width, image->height);
    ImGui::Text("Frame time (fps): %.2fms (%.1f)", io.DeltaTime*1000, 1/io.DeltaTime);
    ImGui::Text("Samples: %d", cam.samples);

    ImGui::SeparatorText("Camera");
    ImGui::DragFloat("Vertical fov", &cam.vfov, 0.1f, 1.0f, 100.0f);
    ImGui::DragFloat("Speed", &cam.speed, 0.1f);
    ImGui::DragFloat2("Sensitivity", glm::value_ptr(cam.sensitivity), 0.1f);
    if (ImGui::Button("Render"))
    {
        cam.render(my_scene);
    }
    ImGui::SameLine();
    ImGui::Checkbox("render every frame", &render_every_frame);

    if (ImGui::Button("Recalculate camera"))
        cam.recalulate_all(image);

    ImGui::End();


    ImGui::Begin("Scene");
    ImGui::ColorEdit3("Directional Light color", glm::value_ptr(my_scene.ambient_color), ImGuiColorEditFlags_Float);
    // ImGui::ColorEdit3("Directional Light color", glm::value_ptr(my_scene.light_color), ImGuiColorEditFlags_Float);
    // ImGui::DragFloat3("Directional Light direction", glm::value_ptr(my_scene.light_direction), 0.1f, -1.0f, 1.0f);
    if (ImGui::Button("Add Sphere")) {
        my_scene.add_object(std::make_shared<Sphere>(glm::vec3(10,0,0),1,0));;
    }
    if (ImGui::TreeNode("Objects"))
    {
        for (size_t i = 0; i < my_scene.objects.size(); i++)
        {
            auto object = my_scene.objects.at(i);
            ImGui::PushID(i);
            object->draw_attributes();
            // ImGui::DragFloat3("radius", glm::value_ptr(o.position));
            ImGui::PopID();
        }
        ImGui::TreePop();
    }

    ImGui::SetNextItemOpen(true, ImGuiCond_Once);
    if (ImGui::TreeNode("Materials"))
    {
        for (size_t i = 0; i < my_scene.materials.size(); i++)
        {
            ImGui::PushID(i);
            auto material = my_scene.materials.at(i);
            ImGui::SetNextItemOpen(true, ImGuiCond_Once);
            auto name = material->get_name();
            if (ImGui::TreeNode("a"))
            {
                material->draw_attributes();
                ImGui::TreePop();
            }
            ImGui::PopID();
        }
        ImGui::TreePop();
    }

    ImGui::End();

    // draw our rendered image to the viewport
    image->draw_image();

};
