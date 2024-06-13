#include "RyeTracer.h"

#include <memory>
#include <cstdint>
#include <iostream>

#include "glm/gtc/type_ptr.hpp"

#include "Camera.h"
#include "Image.h"
#include "imgui.h"
#include "Scene.h"
#include "Sphere.h"


using namespace Barley;

BarleyTracer::BarleyTracer()
{
    m_scene.Initialize();
    // m_camera.Initialize();
}

BarleyTracer::~BarleyTracer()
{

}

void BarleyTracer::AppMenu()
{
    if (ImGui::BeginMenu("Info"))
    {
        ImGui::MenuItem("camera debug", NULL, &m_showCameraDebug);
        ImGui::EndMenu();
    }
}

void BarleyTracer::Update()
{
    ImGuiIO& io = ImGui::GetIO();

    m_camera.OnUpdate(io.DeltaTime);

    if (m_showCameraDebug)
        m_camera.DebugWindow();

    // if (m_renderEveryFrame)
    //     m_renderer.Render();

    ImGui::Begin("Controls");
    ImGui::SeparatorText("Info");
    ImGui::Text("Viewport size: %d x %d", m_camera.film.Width(), m_camera.film.Height());
    ImGui::Text("Frame time (fps): %.2fms (%.1f)", io.DeltaTime*1000, 1/io.DeltaTime);
    ImGui::Text("Samples: %d", m_camera.film.samples);

    ImGui::SeparatorText("Camera");
    m_camera.DrawControls();
    if (ImGui::Button("Render"))
    {
        m_renderer.Render();
    }
    ImGui::SameLine();
    ImGui::Checkbox("render every frame", &m_renderEveryFrame);

    // if (ImGui::Button("Recalculate camera"))
    //     m_camera.ll(image);

    ImGui::End();


    ImGui::Begin("Scene");
    ImGui::ColorEdit3("Directional Light color", glm::value_ptr(m_scene.ambientColor), ImGuiColorEditFlags_Float);
    // ImGui::ColorEdit3("Directional Light color", glm::value_ptr(my_scene.light_color), ImGuiColorEditFlags_Float);
    // ImGui::DragFloat3("Directional Light direction", glm::value_ptr(my_scene.light_direction), 0.1f, -1.0f, 1.0f);
    if (ImGui::Button("Add Sphere")) {
        m_scene.AddObject(std::make_shared<Sphere>(glm::vec4(10,0,0,1),1,0));;
    }
    if (ImGui::TreeNode("Objects"))
    {
        for (size_t i = 0; i < m_scene.objects.size(); i++)
        {
            auto object = m_scene.objects.at(i);
            ImGui::PushID(i);
            object->DrawAttributes();
            // ImGui::DragFloat3("radius", glm::value_ptr(o.position));
            ImGui::PopID();
        }
        ImGui::TreePop();
    }

    ImGui::SetNextItemOpen(true, ImGuiCond_Once);
    if (ImGui::TreeNode("Materials"))
    {
        for (size_t i = 0; i < m_scene.materials.size(); i++)
        {
            ImGui::PushID(i);
            auto material = m_scene.materials.at(i);
            ImGui::SetNextItemOpen(true, ImGuiCond_Once);
            if (ImGui::TreeNode(material->GetName().c_str()))
            {
                material->DrawAttributes();
                ImGui::TreePop();
            }
            ImGui::PopID();
        }
        ImGui::TreePop();
    }

    ImGui::End();

    // draw our rendered image to the viewport
    // image->draw_image();

};
