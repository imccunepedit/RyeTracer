#ifndef GLASS_H_
#define GLASS_H_

#include "Materials.h"

using namespace Rye;

bool GlassBSDF::BSDF(const glm::vec4& inRay, HitData& hit, glm::vec4& scatterRay)
{
    float eta = 1/m_indexOfRefraction;
    float at = 1;

    hit.normal += random_on_sphere(hit.seed) * m_roughness;
    hit.normal = glm::normalize(hit.normal);

    if (hit.inside)
    {
        eta = 1/eta;
        hit.normal *= -1;
    }

    scatterRay = glm::refract(inRay, hit.normal, eta);
    bool reflect = glm::dot(scatterRay, scatterRay) < 0;

    reflect |= Fresnel(inRay, hit.normal, eta) > random_float(hit.seed);

    if (reflect)
        scatterRay = glm::reflect(inRay, hit.normal);

    return true;
}

bool GlassBSDF::Absorb(const glm::vec4& inRay, HitData& hit)
{
    hit.color = glm::vec4(1);

    if (hit.inside)
        hit.color *= glm::exp((m_color-1.0f)*hit.distance);

    return true;
}

bool GlassBSDF::DrawAttributes()
{
    ImGui::ColorEdit3("Color", glm::value_ptr(m_color), ImGuiColorEditFlags_Float);
    ImGui::DragFloat("IoR", &m_indexOfRefraction, 0.002f, 0.0f);
    ImGui::DragFloat("Roughness", &m_roughness, 0.01f, 0, 1);
    ImGui::TreePop();
    return true;
}

std::string GlassBSDF::GetName()
{
    return "Glass BSDF";
}

#endif // GLASS_H_
