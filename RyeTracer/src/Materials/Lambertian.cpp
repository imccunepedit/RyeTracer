#ifndef LAMBERTIAN_H_
#define LAMBERTIAN_H_

#include "Materials.h"

using namespace Rye;

bool LambertianBSDF::BSDF(const glm::vec4& inRay, HitData& hit, glm::vec4& scatterRay)
{
    scatterRay = glm::normalize(hit.normal + random_on_sphere(hit.seed)); //TODO replace 1 with seed
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


#endif // LAMBERTIAN_H_
