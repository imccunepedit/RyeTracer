#ifndef RANDOM_H_
#define RANDOM_H_

#include <cstdint>
#include <limits>

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/geometric.hpp>


namespace raytracing
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

    static glm::vec3 random_in_sphere(uint32_t& seed, float radius=1.0f)
    {
        while(true)
        {
            glm::vec3 out = glm::vec3(random_float(seed)*2-1, random_float(seed)*2-1, random_float(seed)*2-1);
            if (glm::dot(out, out) < 1)
                return out*radius;
        }
        }

        static glm::vec3 random_on_sphere(uint32_t& seed, float radius=1.0f)
    {
        return glm::normalize(random_in_sphere(seed))*radius;
    }
}
#endif // RANDOM_H_
