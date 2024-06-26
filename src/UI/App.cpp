#include "UI/App.h"

#include <memory>
#include <chrono>
#include <future>
#include <cstdint>
#include <iostream>

#include "glm/gtc/type_ptr.hpp"

#include "imgui.h"

#include "Renderer/Camera.h"
#include "Renderer/Scene.h"

using namespace Rye::UI;


App::App()
{
    m_scene.CornellBox();
    // m_scene.Box2();
    // m_scene.TestScene();
    m_camera.Initialize();
}

App::~App()
{
    if (renderThread.valid())
        renderThread.wait();
}

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
    ImGui::Text("Viewport size: %d x %d", m_camera.film.width, m_camera.film.height);
    ImGui::Text("Application frame time (fps): %.2fms (%.1f)", io.DeltaTime*1000, 1/io.DeltaTime);
    ImGui::Text("Last render time: %dms", m_lastRenderMS);

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
    // if (ImGui::Button("Add Sphere")) {
    //     m_scene.AddObject(Object(Transform(glm::vec4(10,0,0,1),1),0));;
    // }

    // if (ImGui::TreeNode("Objects"))
    // {
    //     for (size_t i = 0; i < m_scene.objects.size(); i++)
    //     {
    //         Object& object = m_scene.objects.at(i);
    //         ImGui::PushID(i);

    //         ImGui::SetNextItemOpen(true, ImGuiCond_Once);
    //         if (ImGui::TreeNode("Sphere"))
    //         {
    //             ImGui::DragFloat3("Position", glm::value_ptr(object.transform.position), 0.1f);
    //             ImGui::DragFloat3("Scale", glm::value_ptr(object.transform.scale), 0.1f);
    //             ImGui::DragFloat3("Rotation", glm::value_ptr(object.transform.rotation), 0.1f);
    //             ImGui::SliderInt("Material ID", &object.m_materialID, 0, 10);
    //             ImGui::TreePop();
    //         }

    //         ImGui::PopID();
    //     }
    //     ImGui::TreePop();
    // }

    // ImGui::SetNextItemOpen(true, ImGuiCond_Once);
    // if (ImGui::TreeNode("Materials"))
    // {
    //     for (size_t i = 0; i < m_scene.materialCount; i++)
    //     {
    //         ImGui::PushID(i);
    //         Material& material = m_scene.GetMaterial(i);
    //         ImGui::SetNextItemOpen(true, ImGuiCond_Once);
    //         if (ImGui::TreeNode("material"))
    //         {
    //             ImGui::ColorEdit3("Color", glm::value_ptr(material.color), ImGuiColorEditFlags_Float);
    //             ImGui::DragFloat("Roughness", &material.roughness,0.01,0,1);
    //             ImGui::DragFloat("IoR", &material.indexOfRefraction, 0.002f, 0.0f);
    //             ImGui::DragFloat("Emissive Strength", &material.emissiveStrength, 1.0f, 0.0f);
    //             ImGui::SliderInt("Material Type", &material.materialType, 0, 4);
    //             // material.DrawAttributes();
    //             ImGui::TreePop();
    //         }
    //         ImGui::PopID();
    //     }
    //     ImGui::TreePop();
    // }

    ImGui::End();


    m_camera.OnUpdate(io.DeltaTime);

    if (m_showCameraDebug)
        m_camera.DebugWindow();

    // rendering
    Viewport.Resize();

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

    Viewport.Draw();

};
