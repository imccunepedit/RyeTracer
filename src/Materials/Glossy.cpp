#include "Materials/Glossy.h"

#include "Renderer/Ray.h"
#include "Utils/Random.h"

using namespace Rye::Materials;

bool Glossy::BSDF(const glm::vec3 &inRay, HitData &hit, glm::vec3 &scatterRay) const
{
    if (Utils::RandomFloat(hit.seed) <= specularity)
    {
        scatterRay = glm::normalize(glm::reflect(inRay, hit.normal) + Utils::RandomUnitF3(hit.seed, roughness));
        return true;
    }

    scatterRay = glm::normalize(hit.normal + Utils::RandomUnitF3(hit.seed));

    return true;
}

void Glossy::Color(const glm::vec3 &inRay, HitData &hit) const
{
    uint32_t seed = hit.seed;   // we need to generate the same rendom number later for the scattering ray
    hit.color = (Utils::RandomFloat(seed) <= specularity) ? glm::vec3(1) : color;
}
