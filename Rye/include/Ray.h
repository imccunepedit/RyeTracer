#ifndef RAY_H_
#define RAY_H_

#include <glm/vec4.hpp>
#include <glm/geometric.hpp>

namespace Rye {
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
