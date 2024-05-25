#ifndef RAY_H_
#define RAY_H_

#include <glm/vec3.hpp>
class Ray {
    public:
        Ray(glm::vec3 orig, glm::vec3 dir) : origin(orig), direction(dir) {}

        glm::vec3 at(float t) const{
            return origin + direction * t;
        }

        glm::vec3 origin;
        glm::vec3 direction;
};

#endif // RAY_H_
