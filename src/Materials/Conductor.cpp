#include "Materials/Conductor.h"

#include "Renderer/Ray.h"
#include "Utils/Random.h"
#include "Math/Fresnel.h"

using namespace Rye::Materials;

bool Conductor::BSDF(const glm::vec3 &inRay, HitData &hit, glm::vec3 &scatterRay) const
{
    scatterRay = glm::reflect(inRay, hit.normal) + Utils::RandomUnitF3(hit.seed, roughness);
    return true;
}

void Conductor::Color(const glm::vec3 &inRay, HitData &hit) const
{
    float f = Math::Fresnel(inRay, hit.normal, indexOfRefraction);
    hit.color = (1-f) * color + f;
}
