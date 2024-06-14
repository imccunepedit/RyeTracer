#include "RyeTracer.h"

#include <memory>
#include <cstdint>
#include <iostream>

#include "glm/gtc/type_ptr.hpp"

#include "Camera.h"
#include "imgui.h"
#include "Scene.h"
#include "Sphere.h"


using namespace Barley;

BarleyTracer::BarleyTracer()
{
    m_scene.Initialize();
    // m_camera.Initialize();
}

BarleyTracer::~BarleyTracer() = default;

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
    ImGui::ColorEdit3("Ambient Light color", glm::value_ptr(m_scene.ambientColor), ImGuiColorEditFlags_Float);
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

    ImGui::Begin("Viewport");

    int width = ImGui::GetContentRegionAvail().x;
    int height = ImGui::GetContentRegionAvail().y;

    m_camera.Resize(width, height);

    ImGui::End();

    // m_camera.OnUpdate(io.DeltaTime);

    // if (m_showCameraDebug)
    //     m_camera.DebugWindow();

    // if (m_renderEveryFrame)
    //     m_renderer.Render();

    // draw our rendered image to the viewport
    // image->draw_image();

};
