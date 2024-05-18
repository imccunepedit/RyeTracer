#ifndef RAY_H_
#define RAY_H_

#include <glm/glm.hpp>
class Ray {
    public:
        Ray(glm::dvec3 orig, glm::dvec3 dir) : origin(orig), direction(dir) {}

        glm::dvec3 at(double t) {
            return origin + direction * t;
        }

        glm::dvec3 origin;
        glm::dvec3 direction;
};

#endif // RAY_H_
