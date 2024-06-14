#include "RyeTracer.h"

#include <memory>
#include <cstdint>
#include <iostream>

#include "glm/gtc/type_ptr.hpp"

#include "Camera.h"
#include "imgui.h"
#include "Scene.h"
#include "Sphere.h"

#include "Materials/Lambertian.h"


using namespace Rye;

RyeTracer::RyeTracer()
{
    m_scene.Initialize();
    m_camera.Initialize();
}

RyeTracer::~RyeTracer() = default;

void RyeTracer::AppMenu()
{
    if (ImGui::BeginMenu("Info"))
    {
        ImGui::MenuItem("camera debug", NULL, &m_showCameraDebug);
        ImGui::EndMenu();
    }
}

void RyeTracer::Update()
{
    ImGuiIO& io = ImGui::GetIO();

    ImGui::Begin("Controls");
    ImGui::SeparatorText("Info");
    ImGui::Text("Viewport size: %d x %d", m_camera.film.width, m_camera.film.height);
    ImGui::Text("Frame time (fps): %.2fms (%.1f)", io.DeltaTime*1000, 1/io.DeltaTime);
    ImGui::Text("Samples: %d", m_camera.film.Samples());

    ImGui::SeparatorText("Camera");
    m_camera.DrawControls();

    bool renderThisFrame = ImGui::Button("Render");

    ImGui::SameLine();
    ImGui::Checkbox("render every frame", &m_renderEveryFrame);

    // if (ImGui::Button("Recalculate camera"))
    //     m_camera.ll(image);

    ImGui::End();


    ImGui::Begin("Scene");
    ImGui::ColorEdit3("Ambient Light color", glm::value_ptr(m_scene.ambientColor), ImGuiColorEditFlags_Float);
    if (ImGui::Button("Add Sphere")) {
        m_scene.AddObject(std::make_shared<Sphere>(glm::vec4(10,0,0,1),1,std::make_shared<LambertianBSDF>()));;
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


    m_camera.OnUpdate(io.DeltaTime);

    if (m_showCameraDebug)
        m_camera.DebugWindow();

    // rendering
    Viewport.ReSize();

    if (m_renderEveryFrame || renderThisFrame)
    {
        m_camera.Resize(Viewport.width, Viewport.height);
        m_renderer.Render();
        Viewport.Set(m_camera.film.data);
    }

    Viewport.Draw();

};
