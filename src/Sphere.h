#ifndef SPHERE_H_
#define SPHERE_H_

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/geometric.hpp>

#include "Ray.h"
#include "Hit.h"
#include "Material.h"

class Sphere {
    public:
        Sphere(glm::vec3 c, float r, glm::vec4 co) {
            center = c;
            radius = r;
            material.diffuse = co;
        }

        Hit hit(const Ray &ray);

    public:
        glm::vec3 center;
        float radius;
        Material material;
};

#endif // SPHERE_H_
