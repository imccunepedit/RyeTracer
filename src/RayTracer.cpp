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
}

RayTracer::~RayTracer()
{
    delete image;
}

void RayTracer::Update()
{
    ImGuiIO& io = ImGui::GetIO();

    image->draw_image();

    ImGui::Begin("Controls");

    ImGui::SeparatorText("Camera");
    ImGui::DragFloat3("Position", glm::value_ptr(cam.position));
    ImGui::DragFloat3("Look direction", glm::value_ptr(cam.local_forward));
    ImGui::DragFloat("Focal Distance", &cam.focal_dist);
    if (ImGui::Button("Render"))
    {
        image->width = image->window_width;
        image->height = image->window_height;
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
    ImGui::Text("Viewport size: %d x %d", image->width, image->height);
    ImGui::Text("Frame time (fps): %fms (%f)", ImGui::GetIO().DeltaTime*1000, ImGui::GetIO().Framerate);

    ImGui::SeparatorText("Scene");
    ImGui::ColorEdit4("Sky color", glm::value_ptr(my_scene.sky_color), ImGuiColorEditFlags_Float);
    if (ImGui::Button("Add Sphere")) {
        my_scene.add_sphere(Sphere({10,0,0},1,{1,0,0,1}));;
    }
    ImGui::Spacing();
    if (ImGui::TreeNode("Spheres"))
    {
        for (int i = 0; i < my_scene.spheres.size(); i++)
        {
            ImGui::SetNextItemOpen(true, ImGuiCond_Once);
            if (ImGui::TreeNode((void*)(intptr_t)i, "Sphere %d", i))
            {
                ImGui::ColorEdit4("Color", glm::value_ptr(my_scene.spheres[i].material.diffuse));
                ImGui::DragFloat3("Position", glm::value_ptr(my_scene.spheres[i].center));
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

};
