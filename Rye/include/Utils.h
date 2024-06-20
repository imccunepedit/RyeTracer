#ifndef UTILS_H_
#define UTILS_H_

#include <iostream>

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>


namespace Rye
{
    static void log(std::string info)
    {
        std::cout << info << std::endl;
    }

    static uint32_t pcgHash(uint32_t input)
    {
        uint32_t state = input * 747796405u + 2891336453u;
        uint32_t word = ((state >> ((state >> 28u) + 4u)) ^ state) * 277803737u;
        return (word >> 22u) ^ word;
    }

    static float RandomFloat(uint32_t& seed)
    {
        seed = pcgHash(seed);
        return seed / (float) std::numeric_limits<uint32_t>::max();
    }

    static glm::vec3 RandomInSphere(uint32_t& seed, float radius=1.0f)
    {
        while(true)
        {
            glm::vec3 out = glm::vec3(RandomFloat(seed)*2-1, RandomFloat(seed)*2-1, RandomFloat(seed)*2-1);
            if (glm::dot(out, out) < 1)
                return out*radius;
        }
    }


    static glm::vec3 RandomOnSphere(uint32_t& seed, float radius=1.0f)
    {
        return glm::normalize(RandomInSphere(seed))*radius;
    }


    static float Fresnel(glm::vec3 I, glm::vec3 N, float eta)
    {
        float c1 = glm::dot(I,-N);
#define SCHLICK
#ifdef SCHLICK
        float R0 = (1-eta)/(1+eta);
        R0 *= R0;
        return R0 + (1-R0)*pow((1 - c1),5);
#else
        float inverse_eta = 1/eta;
        float c2 = sqrtf(1 - inverse_eta*inverse_eta * (1 - c1*c1));
        float Rs = (c1 - eta*c2) / (c1 + eta*c2);
        float Rp = (c2 - eta*c1) / (c2 + eta*c1);
        return 0.5f * (Rs*Rs + Rp*Rp);
#endif
    }


}
#endif // UTILS_H_
