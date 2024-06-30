#include "Materials/Dielectric.h"

#include "Renderer/Ray.h"
#include "Utils/Random.h"
#include "Math/Fresnel.h"

#include "Utils/Log.h"

using namespace Rye::Materials;

bool Dielectric::BSDF(const glm::vec3 &inRay, HitData &hit, glm::vec3 &scatterRay) const
{
    float eta = hit.front ? 1.0f/indexOfRefraction : indexOfRefraction;
    hit.normal *= hit.front ? 1.0f : -1.0f;

    // hit.normal += RandomOnSphere(hit.seed, roughness);
    // hit.normal = glm::normalize(hit.normal);

    float sinesq = Math::SineThetaSqr(glm::dot(inRay, -hit.normal), eta);

    bool reflect = sinesq < 0.0f;
    // if (reflect)
    // {
    //     hit.color = glm::vec3(1,0,0);
    //     // scatterRay = glm::reflect(glm::normalize(inRay), glm::normalize(hit.normal));
    //     return false;
    // }

    if (!reflect)
        reflect = Math::Fresnel(inRay, hit.normal, eta) > Utils::RandomFloat(hit.seed);

    if (!reflect)
        scatterRay = glm::refract(inRay, hit.normal, eta);
    else
        scatterRay = glm::reflect(inRay, hit.normal);

    return true;
}


void Dielectric::Color(const glm::vec3 &inRay, HitData &hit) const
{
    // hit.color = hit.normal;
    hit.color = glm::vec3(1);
    // if (!hit.front)
    //     hit.color = glm::exp((color-1.0f)*hit.distance);
}
