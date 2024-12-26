#include "App.h"

#include <iostream>

#include "imgui.h"

using namespace Rye;

App::App() {}

App::~App() = default;

void App::AppMenu() {}

void App::ImGuiDraw()
{
    ImGui::Begin("TEST");
    ImGui::Text("test");
    ImGui::End();
};
