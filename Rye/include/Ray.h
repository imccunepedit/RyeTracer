#ifndef RAY_H_
#define RAY_H_

#include <memory>

#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

namespace Rye {
    class Material;
    struct HitData {
        glm::vec3 point;
        glm::vec3 normal;
        glm::vec3 color = glm::vec3(0,0,0);
        float distance = std::numeric_limits<float>::max();
        bool front = true;
        uint32_t materialID = 0;

        uint32_t seed = 1;
    };

    class Ray {
        public:
            glm::vec3 at(float t) const
            {
                return origin + direction * t;
            }

            glm::vec3 origin;
            glm::vec3 direction;
            uint32_t seed;
            int depth = 0;
    };
}

#endif // RAY_H_
