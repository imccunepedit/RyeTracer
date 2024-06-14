#ifndef GLOSSY_H_
#define GLOSSY_H_

#include "Materials.h"

using namespace Rye;

bool GlossyBSDF::BSDF(const glm::vec4& inRay, HitData& hit, glm::vec4& scatterRay)
{
    if (random_float(hit.seed) > m_specularProb)
    {
        m_diffuse.BSDF(inRay, hit, scatterRay);
        return true;
    }
    m_spec.BSDF(inRay, hit, scatterRay);
    return true;
}

bool GlossyBSDF::Absorb(const glm::vec4& inRay, HitData& hit)
{
    hit.color = glm::vec4(1);
    return true;
}

bool GlossyBSDF::DrawAttributes()
{
    m_diffuse.DrawAttributes();
    m_spec.DrawAttributes();
    ImGui::DragFloat("Specular probability", &m_specularProb, 0.01f, 0,1);
    return true;
}

std::string GlossyBSDF::GetName()
{
    return "Glossy BSDF";
}



#endif // GLOSSY_H_
