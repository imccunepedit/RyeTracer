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
    float f = Math::Fresnel(glm::dot(inRay, -hit.normal), 1/indexOfRefraction);
    // hit.color = color;
    hit.color = (1-f) * color + glm::vec3(1) * f;
}
