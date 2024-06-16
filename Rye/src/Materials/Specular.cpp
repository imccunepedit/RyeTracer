#include "Materials/Specular.h"

#include <glm/gtc/type_ptr.hpp>

#include "imgui.h"

#include "Utils.h"
#include "Ray.h"

using namespace Rye;
bool SpecularBSDF::BSDF(const glm::vec4& inRay, HitData& hit, glm::vec4& scatterRay)
{
    hit.color = m_color;
    scatterRay = glm::normalize(glm::reflect(inRay, hit.normal) + RandomOnSphere(hit.seed) * m_roughness);

    return true;
}

bool SpecularBSDF::Absorb(const glm::vec4 &inRay, HitData &hit)
{
    hit.color = m_color;
    return true;
}

bool SpecularBSDF::DrawAttributes()
{
    ImGui::PushID((int*) "specular");
    ImGui::ColorEdit3("Color", glm::value_ptr(m_color), ImGuiColorEditFlags_Float);
    ImGui::DragFloat("Roughness", &m_roughness, 0.01f, 0, 1);
    ImGui::PopID();
    return true;
}

std::string SpecularBSDF::GetName()
{
    return "Specular BSDF";
}
