#include "Materials/Emissive.h"

#include "Renderer/Ray.h"

using namespace Rye::Materials;

Emissive::Emissive(float strength)
    : emissiveStrength(strength)
{}

Emissive::Emissive(glm::vec3 color,float strength)
    : color(color), emissiveStrength(strength)
{}

void Emissive::Color(const glm::vec3 &inRay, HitData &hit) const
{
    hit.color = color * emissiveStrength;
}
