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

    static float Schlick(glm::vec3 I, glm::vec3 N, float eta)
    {
        float c1 = glm::dot(I, -N);
        float R0 = (1 - eta) / (1 + eta);
        R0 *= R0;
        return R0 + (1 - R0) * pow((1 - c1), 5);
    }

    static float Fresnel(glm::vec3 I, glm::vec3 N, float eta)
    {
        float c1 = glm::dot(I, -N);
        float c2 = glm::sqrt(SineThetaSqr(c1, 1/eta));
        float Rs = (c1 - eta * c2) / (c1 + eta * c2);
        float Rp = (c2 - eta * c1) / (c2 + eta * c1);
        return 0.5f * (Rs * Rs + Rp * Rp);
    }


}
// namespace Rye::Math

#endif /* FRESNEL_H */
