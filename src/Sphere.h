#ifndef SPHERE_H_
#define SPHERE_H_

#include <glm/glm.hpp>

#include "Ray.h"
#include "Hit.h"

class Sphere {
    public:
        Sphere(glm::dvec3 c, double r) : center(c), radius(r) {}

        bool hit(Ray &ray, Hit &hit);

    public:
        glm::dvec3 center;
        double radius;
        glm::vec4 color;
};

#endif // SPHERE_H_
