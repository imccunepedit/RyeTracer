#ifndef SPHERE_H_
#define SPHERE_H_

#include <glm/glm.hpp>

#include "Ray.h"
#include "Hit.h"

class Sphere {
    public:
        Sphere(glm::vec3 c, float r, glm::vec4 co) : center(c), radius(r), color(co) {}

        Hit hit(Ray &ray);

    public:
        glm::vec3 center;
        float radius;
        glm::vec4 color = {0,1,0,1};
};

#endif // SPHERE_H_
