#ifndef UTILS_H_
#define UTILS_H_

#include <cstdint>

#include <glm/vec4.hpp>
#include <glm/geometric.hpp>


namespace Rye
{
    static uint32_t pcg_hash(uint32_t input)
    {
        uint32_t state = input * 747796405u + 2891336453u;
        uint32_t word = ((state >> ((state >> 28u) + 4u)) ^ state) * 277803737u;
        return (word >> 22u) ^ word;
    }

    static float random_float(uint32_t& seed)
    {
        seed = pcg_hash(seed);
        return seed / (float) std::numeric_limits<uint32_t>::max();
    }

    static glm::vec4 random_in_sphere(uint32_t& seed, float radius=1.0f)
    {
        while(true)
        {
            glm::vec4 out = glm::vec4(random_float(seed)*2-1, random_float(seed)*2-1, random_float(seed)*2-1, 0);
            if (glm::dot(out, out) < 1)
                return out*radius;
        }
    }


    static glm::vec4 random_on_sphere(uint32_t& seed, float radius=1.0f)
    {
        return glm::normalize(random_in_sphere(seed))*radius;
    }

}
#endif // UTILS_H_
