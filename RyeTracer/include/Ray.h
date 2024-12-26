#ifndef RAY_H_
#define RAY_H_

#include <memory>

#include <glm/vec4.hpp>
#include <glm/geometric.hpp>

namespace Rye {
    class Material;
    struct HitData {
        glm::vec4 point;
        glm::vec4 normal;
        glm::vec4 color = glm::vec4(0,0,0,1);
        float distance = std::numeric_limits<float>::max();
        bool front = true;
        std::shared_ptr<Material> material = nullptr;

        uint32_t seed = 1;
    };

    class Ray {
        public:
            glm::vec4 at(float t) const{
                return origin + direction * t;
            }

            glm::vec4 origin;
            glm::vec4 direction;
            uint32_t seed;
            int depth = 0;
    };
}

#endif // RAY_H_
