#ifndef FRESNEL_H
#define FRESNEL_H

#include <glm/geometric.hpp>
#include <glm/vec3.hpp>

namespace Rye::Math
{
    static float SineThetaSqr(float cosTheta, float eta)
    // calculated the sqaure of the sin of the angle of the refracted ray
    {
        return 1 - eta * eta * (1 - cosTheta * cosTheta);
    }

    static float Schlick(float cosineTheta, float eta)
    {
        float R0 = (1 - eta) / (1 + eta);
        R0 *= R0;
        return R0 + (1 - R0) * pow((1 - cosineTheta), 5);
    }

    static float Fresnel(float cosineTheta_i, float eta)
    {
        float cosineTheta_t = glm::sqrt(glm::max(0.0f, SineThetaSqr(glm::min(cosineTheta_i, 1.0f), eta)));
        float Rs = (cosineTheta_i * eta - cosineTheta_t) / (cosineTheta_i * eta + cosineTheta_t);
        float Rp = (cosineTheta_t * eta - cosineTheta_i) / (cosineTheta_t * eta + cosineTheta_i);
        return 0.5f * (Rs * Rs + Rp * Rp);
    }


}
// namespace Rye::Math

#endif /* FRESNEL_H */
