#include "Materials/Glossy.h"

#include "Renderer/Ray.h"
#include "Utils/Random.h"

using namespace Rye::Materials;

bool Glossy::BSDF(const glm::vec3 &inRay, HitData &hit, glm::vec3 &scatterRay) const
{
    if (m_isSpecular)
    {
        scatterRay = glm::normalize(glm::reflect(inRay, hit.normal) + Utils::RandomUnitF3(hit.seed) * roughness);
        return true;
    }

    scatterRay = glm::normalize(hit.normal + Utils::RandomUnitF3(hit.seed));
    return true;
}

void Glossy::Color(const glm::vec3 &inRay, HitData &hit) const
{
    if (Utils::RandomFloat(hit.seed) <= specularity)
    {
        m_isSpecular = true;
        hit.color = glm::vec3(1);
        return;
    }
    m_isSpecular = false;
    hit.color = color;
}
