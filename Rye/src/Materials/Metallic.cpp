#include "Materials/Metallic.h"

#include <glm/gtc/type_ptr.hpp>

#include "imgui.h"

#include "Utils.h"
#include "Ray.h"

using namespace Rye;

bool MetallicBSDF::BSDF(const glm::vec4& inRay, HitData& hit, glm::vec4& scatterRay)  {
    scatterRay = glm::reflect(inRay, hit.normal) + RandomOnSphere(hit.seed) * m_roughness;
    return true;
}

bool MetallicBSDF::Absorb(const glm::vec4& inRay, HitData& hit)
{
    float f = Fresnel(inRay, hit.normal, 0.2f);
    hit.color = (1-f) * m_color + f * glm::vec4(1);
    return true;
}

bool MetallicBSDF::DrawAttributes()
{
    ImGui::ColorEdit3("Color", glm::value_ptr(m_color), ImGuiColorEditFlags_Float);
    ImGui::DragFloat("Roughness", &m_roughness,0.01,0,1);
    return true;
}

std::string MetallicBSDF::GetName()
{
    return "Metallic BSDF";
}
