#include "App.h"

#include <memory>
#include <chrono>
#include <future>
#include <cstdint>
#include <iostream>

#include "glm/gtc/type_ptr.hpp"

#include "imgui.h"

#include "Camera.h"
#include "Scene.h"
#include "Objects/Sphere.h"
#include "Materials/Lambertian.h"

using namespace Barley;
using namespace Rye;

App::App()
: Compute(Shader("Rye/Shaders/RayTracing.comp"))
{
    m_scene.Initialize();
    m_camera.Initialize();
}

App::~App() = default;

void App::AppMenu()
{
    if (ImGui::BeginMenu("Info"))
    {
        ImGui::MenuItem("camera debug", NULL, &m_showCameraDebug);
        ImGui::EndMenu();
    }
}

void App::Update()
{
    ImGuiIO& io = ImGui::GetIO();

    ImGui::Begin("Info");
    ImGui::SeparatorText("Info");
    ImGui::Text("Viewport size: %d x %d", Viewport.width, Viewport.height);
    ImGui::Text("Application frame time (fps): %.2fms (%.1f)", io.DeltaTime*1000, 1/io.DeltaTime);
    ImGui::Text("Last render time: %dms", m_lastRenderMS);
    if (ImGui::Button("Relod Shaders"))
        Compute.Load();

    ImGui::SeparatorText("Camera");
    m_camera.DrawControls();

    ImGui::SeparatorText("Renderer");
    m_renderer.DrawControls();

    bool renderThisFrame = ImGui::Button("Render");
    ImGui::SameLine();
    ImGui::Checkbox("render every frame", &m_renderEveryFrame);


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
    Viewport.Resize();

#define GPU
#ifndef GPU
    if ((m_renderEveryFrame || renderThisFrame) && !m_rendering)
    {
        m_camera.Resize(Viewport.width, Viewport.height);
        renderThread = std::async(std::launch::async, &Renderer::Render, m_renderer);
        m_rendering = true;
    }

    if (renderThread.valid())
    {
        using namespace std::chrono_literals;
        auto status = renderThread.wait_for(0ms);
        if ((status == std::future_status::ready) && m_rendering)
        {
            m_lastRenderMS = renderThread.get();
            Viewport.Set(m_camera.film.data);
            m_rendering = false;
        }
    }

#else
    Viewport.BindImage();
    Compute.Use();
    Compute.SetMat4("inverseView", m_camera.inverseView);
    Compute.SetMat4("inverseProjection", m_camera.inverseProjection);
    Compute.SetVec4("cameraPosition", m_camera.position);


    Compute.SetVec4("Materials[0].color", glm::vec4(0.5f));

    Compute.SetVec4("Objects[0].position", glm::vec4(0,0,1,1));
    Compute.SetFloat("Objects[0].raidius", 1.0f);
    Compute.SetInt("Objects[0].materialID", 0);

    Compute.SetVec4("Objects[1].position", glm::vec4(0,0,-1000,1));
    Compute.SetFloat("Objects[1].raidius", 1000);
    Compute.SetInt("Objects[1].materialID", 0);

    Compute.SetVec4("Objects[2].position", glm::vec4(4,0,1,1));
    Compute.SetFloat("Objects[2].raidius", 1.0f);
    Compute.SetInt("Objects[2].materialID", 0);


    glDispatchCompute((unsigned int)Viewport.width, (unsigned int)Viewport.height, 1);

    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
#endif

    Viewport.Draw();

};
