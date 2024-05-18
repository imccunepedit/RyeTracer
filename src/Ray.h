#ifndef RAY_H_
#define RAY_H_

#include <glm/glm.hpp>
class Ray {
    public:
        Ray(glm::dvec3 orig, glm::dvec3 dir) {}

        glm::vec3 at(double t) {
            return origin + direction * t;
        }

    private:
        glm::dvec3 origin;
        glm::dvec3 direction;
};

#endif // RAY_H_
