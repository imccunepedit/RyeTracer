#ifndef SPHERE_H_
#define SPHERE_H_

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

#include "Ray.h"
#include "Hit.h"
#include "Material.h"

class Sphere {
    public:
        Sphere(glm::vec3 c, float r, Material material) : center(c), radius(r), material(material) {}

        bool hit(const Ray &ray, Hit& hit);

    public:
        glm::vec3 center;
        float radius;
        Material material;
};

#endif // SPHERE_H_
