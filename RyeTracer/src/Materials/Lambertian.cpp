#include "Materials/Lambertian.h"

#include <glm/gtc/type_ptr.hpp>

#include "imgui.h"

#include "Utils.h"
#include "Ray.h"

using namespace Rye;

bool LambertianBSDF::BSDF(const glm::vec4& inRay, HitData& hit, glm::vec4& scatterRay)
{
    scatterRay = glm::normalize(hit.normal + RandomOnSphere(hit.seed)); //TODO replace 1 with seed
    return true;
}

bool LambertianBSDF::Absorb(const glm::vec4& inRay, HitData& hit)
{
    hit.color = m_color;
    return true;
}

bool LambertianBSDF::DrawAttributes()
{
    ImGui::ColorEdit3("Color", glm::value_ptr(m_color), ImGuiColorEditFlags_Float);
    return true;
}

std::string LambertianBSDF::GetName()
{
    return "Diffuse BSDF";
}
