#include "App.h"

#include <iostream>
// #include <chrono>
// #include <future>
// #include <cstdint>
// #include <iostream>

// #include "glm/gtc/type_ptr.hpp"

// #include "imgui.h"

// #include "Camera.h"
// #include "Scene.h"
// #include "Objects/Sphere.h"
// #include "Materials/Lambertian.h"

// using namespace Rye;

using namespace Barley;

App::App()
{
    // m_scene.Initialize();
    // m_camera.Initialize();
}

App::~App() = default;

void App::AppMenu()
{
    // if (ImGui::BeginMenu("Info"))
    // {
    //     ImGui::MenuItem("camera debug", NULL, &m_showCameraDebug);
    //     ImGui::EndMenu();
    // }
}

void App::Update()
{
    std::cout << 1 << std::endl;
    // ImGuiIO& io = ImGui::GetIO();

    // ImGui::Begin("Info");
    // ImGui::SeparatorText("Info");
    // ImGui::Text("Viewport size: %d x %d", m_camera.film.width, m_camera.film.height);
    // ImGui::Text("Application frame time (fps): %.2fms (%.1f)", io.DeltaTime*1000, 1/io.DeltaTime);
    // ImGui::Text("Last render time: %dms", m_lastRenderMS);

    // ImGui::SeparatorText("Camera");
    // m_camera.DrawControls();

    // ImGui::SeparatorText("Renderer");
    // m_renderer.DrawControls();

    // bool renderThisFrame = ImGui::Button("Render");
    // ImGui::SameLine();
    // ImGui::Checkbox("render every frame", &m_renderEveryFrame);


    // ImGui::End();


    // ImGui::Begin("Scene");
    // ImGui::ColorEdit3("Ambient Light color", glm::value_ptr(m_scene.ambientColor), ImGuiColorEditFlags_Float);
    // if (ImGui::Button("Add Sphere")) {
    //     m_scene.AddObject(std::make_shared<Sphere>(glm::vec4(10,0,0,1),1,std::make_shared<LambertianBSDF>()));;
    // }

    // if (ImGui::TreeNode("Objects"))
    // {
    //     for (size_t i = 0; i < m_scene.objects.size(); i++)
    //     {
    //         auto object = m_scene.objects.at(i);
    //         ImGui::PushID(i);
    //         object->DrawAttributes();
    //         ImGui::PopID();
    //     }
    //     ImGui::TreePop();
    // }

    // ImGui::SetNextItemOpen(true, ImGuiCond_Once);
    // if (ImGui::TreeNode("Materials"))
    // {
    //     for (size_t i = 0; i < m_scene.materials.size(); i++)
    //     {
    //         ImGui::PushID(i);
    //         auto material = m_scene.materials.at(i);
    //         ImGui::SetNextItemOpen(true, ImGuiCond_Once);
    //         if (ImGui::TreeNode(material->GetName().c_str()))
    //         {
    //             material->DrawAttributes();
    //             ImGui::TreePop();
    //         }
    //         ImGui::PopID();
    //     }
    //     ImGui::TreePop();
    // }

    // ImGui::End();


    // m_camera.OnUpdate(io.DeltaTime);

    // if (m_showCameraDebug)
    //     m_camera.DebugWindow();

    // // rendering
    // Viewport.Resize();

    // if ((m_renderEveryFrame || renderThisFrame) && !m_rendering)
    // {
    //     m_camera.Resize(Viewport.width, Viewport.height);
    //     renderThread = std::async(std::launch::async, &Renderer::Render, m_renderer);
    //     m_rendering = true;
    // }

    // if (renderThread.valid())
    // {
    //     using namespace std::chrono_literals;
    //     auto status = renderThread.wait_for(0ms);
    //     if ((status == std::future_status::ready) && m_rendering)
    //     {
    //         m_lastRenderMS = renderThread.get();
    //         Viewport.Set(m_camera.film.data);
    //         m_rendering = false;
    //     }
    // }

    // Viewport.Draw();

};
