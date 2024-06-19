#include "App.h"

#include <iostream>

#include "imgui.h"

using namespace Barley;

App::App() {}

App::~App() = default;

void App::AppMenu() {}

void App::ImGuiDraw()
{
    ImGui::Begin("TEST");
    ImGui::Text("test");
    ImGui::End();
};
