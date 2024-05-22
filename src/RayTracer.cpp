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
    my_scene.load_default();
}

void RayTracer::Update()
{
    // window containing our rendered image
    // remove padding
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f,0.0f));
    // 24 (8+16) remove scrollbars and scrolling
    ImGui::Begin("Viewport", NULL, 24);
    // keep track of the window size
    viewport_width = ImGui::GetContentRegionAvail().x;
    viewport_height = ImGui::GetContentRegionAvail().y;

    // our images actual width and height, viewport may have changed size
    ImVec2 image_size = ImVec2(image->width, image->height);
    ImTextureID image_id = (void*)(intptr_t)image->texture;

    // tell ImGui how to orient our image
    ImVec2 uv0 = ImVec2(0.0f,0.0f);
    ImVec2 uv1 = ImVec2(1.0f,1.0f);

    // draw the image into the viewport
    ImGui::Image(image_id, image_size, uv0, uv1);

    if (ImGui::BeginItemTooltip())
    {
        ImGuiIO& io = ImGui::GetIO();
        ImVec2 region_size = ImVec2(10, 10);
        float region_zoom = 10;
        ImVec2 region0 = {io.MousePos.x, io.MousePos.y};
        ImVec2 region1 = {io.MousePos.x + region_size.x, io.MousePos.y + region_size.y};
        if (region1.x > image_size.x)
        {
            region1.x = image_size.x;
            region0.x = image_size.x - region_size.x;
        }
        if (region1.y > image_size.y)
        {
            region1.y = image_size.y;
            region0.y = image_size.y - region_size.y;
        }
        ImVec2 ttuv0 = ImVec2(region0.x / image_size.x, region0.y/image_size.y);
        ImVec2 ttuv1 = ImVec2(region1.x / image_size.x, region1.y/image_size.y);
        ImGui::Text("Zoom: %.2f", region_zoom);
        ImGui::Text("Min: (%.2f, %.2f)",region0.x, region0.y);
        ImGui::Text("Max: (%.2f, %.2f)",region1.x, region1.y);
        ImGui::Image(image_id, ImVec2(region_size.x*region_zoom, region_size.y*region_zoom), ttuv0, ttuv1);
        ImGui::EndTooltip();
    }


    ImGui::End();
    ImGui::PopStyleVar();


    ImGui::Begin("Controls");

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
