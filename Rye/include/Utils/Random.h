#ifndef UTILS_H_
#define UTILS_H_

#include <iostream>

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>


namespace Rye::Utils
{

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


    static glm::vec3 RandomUnitF3(uint32_t& seed, float radius=1.0f)
    {
        return glm::normalize(RandomInSphere(seed))*radius;
    }



    struct Complex
    {
        float a,b;

    };


}
#endif // UTILS_H_
