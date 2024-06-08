#ifndef SPHERE_H_
#define SPHERE_H_

#include "Object.h"

#include <glm/vec3.hpp>


#include "Ray.h"
#include "Hit.h"

class Sphere : public Object {
    public:
        Sphere(glm::vec3 c, float r, uint32_t m_id) : position(c), radius(r), material_id(m_id) {}

        bool hit(const Ray &ray, Hit& hit) const override;

    public:
        glm::vec3 position;
        float radius;
        uint32_t material_id;
};

#endif // SPHERE_H_
