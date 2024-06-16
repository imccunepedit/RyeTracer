#include "Materials/Emission.h"

#include <glm/gtc/type_ptr.hpp>

#include "imgui.h"

#include "Ray.h"

using namespace Rye;

bool Emission::Absorb(const glm::vec4& in_ray, HitData& hit)
{
    hit.color =  m_color * m_strength;
    return true;
}

bool Emission::DrawAttributes()
{
    ImGui::ColorEdit3("Color", glm::value_ptr(m_color), ImGuiColorEditFlags_Float);
    ImGui::DragFloat("Strength", &m_strength, 1.0f, 0.0f);
    return true;
}

std::string Emission::GetName()
{
    return "Emmisive";
}
