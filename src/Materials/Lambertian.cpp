#include "Materials/Lambertian.h"

#include "Renderer/Ray.h"
#include "Utils/Random.h"

using namespace Rye::Materials;

bool Lambertian::BSDF(const glm::vec3 &inRay, HitData &hit, glm::vec3 &scatterRay) const
{
    scatterRay = glm::normalize(hit.normal + Rye::Utils::RandomUnitF3(hit.seed));
    return true;
}

void Lambertian::Color(const glm::vec3 &inRay, HitData &hit) const
{
    hit.color = color;
}
