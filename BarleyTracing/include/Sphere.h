#ifndef SPHERE_H_
#define SPHERE_H_

#include "Object.h"

#include <glm/vec4.hpp>

#include "Ray.h"
#include "HitData.h"

class Sphere : public Object {
    public:
        Sphere(glm::vec4 position, float radius, uint32_t materialID) : m_position(position), m_radius(radius), m_materialID(materialID) {}

        bool Hit(const Ray &ray, HitData& hit) const override;
        bool DrawAttributes() override;

    private:
        glm::vec4 m_position;
        float m_radius;
        uint32_t m_materialID;
};

#endif // SPHERE_H_
