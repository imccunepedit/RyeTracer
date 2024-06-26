#include "Materials/Emissive.h"

#include "Renderer/Ray.h"

using namespace Rye::Materials;

void Emissive::Color(const glm::vec3 &inRay, HitData &hit) const
{
    hit.color = color * emissiveStrength;
}
