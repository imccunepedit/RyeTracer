#include "Assets/Material.h"

#include "Renderer/Ray.h"
#include "Utils/Random.h"
#include "Math/Fresnel.h"

using namespace Rye;
using namespace Rye::Math;
using namespace Rye::Utils;

bool Material::BSDF(const glm::vec3& inRay, HitData& hit, glm::vec3& scatterRay) const
{
    switch (materialType) {
        case Lambertian:
            scatterRay = glm::normalize(hit.normal + RandomUnitF3(hit.seed));
            return true;

        case Conductor:
            scatterRay = glm::reflect(inRay, hit.normal) + RandomUnitF3(hit.seed, roughness);
            return true;

        case Dielectric:
            return DielectricBSDF(inRay, hit, scatterRay);

        case Glossy:
            return GlossyBSDF(inRay, hit, scatterRay);

        default:
            break;
    }

    return false;
}

void Material::Color(const glm::vec3& inRay, HitData& hit)
{
    switch (materialType) {
        default:
            hit.color = color;
            return;

        case Dielectric:
            hit.color = glm::vec3(1);
            if (!hit.front)
                hit.color = glm::exp((color-1.0f)*hit.distance);
            return;

        case Emissive:
            hit.color =  color * emissiveStrength;
            return;

        case Glossy:
            if (RandomFloat(hit.seed) <= specularity*Fresnel(inRay, hit.normal, indexOfRefraction))
            {
                m_isSpecular = true;
                hit.color = glm::vec3(1);
                return;
            }
            m_isSpecular = false;
            hit.color = color;
            return;

        case Conductor:
            float f = Fresnel(inRay, hit.normal, indexOfRefraction);
            hit.color = (1-f) * color + f;
            return;
    }

}

bool Material::DielectricBSDF(const glm::vec3& inRay, HitData& hit, glm::vec3& scatterRay) const
{
    float eta = hit.front ? 1/indexOfRefraction : indexOfRefraction;
    hit.normal *= hit.front ? 1.0f : -1.0f;

    // hit.normal += RandomOnSphere(hit.seed, roughness);
    // hit.normal = glm::normalize(hit.normal);

    scatterRay = glm::refract(inRay, hit.normal, eta);
    bool reflect = glm::dot(scatterRay, scatterRay) < 0;

    reflect |= Fresnel(inRay, hit.normal, eta) > RandomFloat(hit.seed);

    if (reflect)
        scatterRay = glm::reflect(inRay, hit.normal);

    return true;
}

bool Material::GlossyBSDF(const glm::vec3& inRay, HitData& hit, glm::vec3& scatterRay) const
{
    if (m_isSpecular)
    {
        scatterRay = glm::normalize(glm::reflect(inRay, hit.normal) + RandomUnitF3(hit.seed) * roughness);
        return true;
    }

    scatterRay = glm::normalize(hit.normal + RandomUnitF3(hit.seed));
    return true;
}
