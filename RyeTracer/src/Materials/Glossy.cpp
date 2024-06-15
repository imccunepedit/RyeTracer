#ifndef GLOSSY_H_
#define GLOSSY_H_

#include "Materials.h"

#include <iostream>

using namespace Rye;

bool GlossyBSDF::BSDF(const glm::vec4& inRay, HitData& hit, glm::vec4& scatterRay)
{
    // if (m_isSpecular)
    // {
    //     m_spec.BSDF(inRay, hit, scatterRay);
    //     return true;
    // }

    // m_diffuse.BSDF(inRay, hit, scatterRay);
    std::cout << "should not have run till here" << std::endl;
    return false;
}

bool GlossyBSDF::Absorb(const glm::vec4& inRay, HitData& hit)
{
    if (random_float(hit.seed) <= m_specularity)
    {
        hit.material = std::make_shared<SpecularBSDF>(m_spec);
        m_spec.Absorb(inRay, hit);
        return true;
    }

    m_diffuse.Absorb(inRay, hit);
    hit.material = std::make_shared<LambertianBSDF>(m_diffuse);

    return true;
}

bool GlossyBSDF::DrawAttributes()
{
    m_diffuse.DrawAttributes();
    m_spec.DrawAttributes();
    ImGui::DragFloat("Specular probability", &m_specularity, 0.01f, 0,1);
    return true;
}

std::string GlossyBSDF::GetName()
{
    return "Glossy BSDF";
}



#endif // GLOSSY_H_
