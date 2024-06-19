#include "Material.h"

#include "Ray.h"
#include "Utils.h"

using namespace Rye;

bool Material::BSDF(const glm::vec3& inRay, HitData& hit, glm::vec3& scatterRay)
{
    switch (materialType) {
        case Lambertian:
            scatterRay = glm::normalize(hit.normal + RandomOnSphere(hit.seed));
            return true;

        // case Conductor:
        //     scatterRay = glm::reflect(inRay, hit.normal) + RandomOnSphere(hit.seed) * roughness;
        //     return true;

        // case Dielectric:
        //     return DielectricBSDF(inRay, hit, scatterRay);

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
            hit.color = glm::vec4(1);
            if (!hit.front)
                hit.color *= glm::exp((color-1.0f)*hit.distance);
            return;

        case Emissive:
            hit.color =  color * emissiveStrength;
            return;

        // case Conductor:
        //     float f = Fresnel(inRay, hit.normal, 0.2f);
        //     hit.color = (1-f) * color + f * glm::vec4(1);
        //     return;
    }

}

bool Material::DielectricBSDF(const glm::vec3& inRay, HitData& hit, glm::vec3& scatterRay)
{
    float eta = 1/indexOfRefraction;
    float at = 1;

    hit.normal += RandomOnSphere(hit.seed) * roughness;
    hit.normal = glm::normalize(hit.normal);

    if (!hit.front)
    {
        eta = 1/eta;
        hit.normal *= -1;
    }

    scatterRay = glm::refract(inRay, hit.normal, eta);
    bool reflect = glm::dot(scatterRay, scatterRay) < 0;

    reflect |= Fresnel(inRay, hit.normal, eta) > RandomFloat(hit.seed);

    if (reflect)
        scatterRay = glm::reflect(inRay, hit.normal);

    return true;
}
