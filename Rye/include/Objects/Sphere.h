#ifndef SPHERE_H_
#define SPHERE_H_

#include <memory>

#include "Object.h"

namespace Rye {
    class Material;

    class Sphere : public Object {
        public:
            Sphere(glm::vec4 position, float radius, int materialID)
                : m_position(position), m_radius(radius), m_materialID(materialID) {}

            bool Hit(const Ray &ray, HitData& hit) const override;

        public:
            glm::vec4 m_position;
            float m_radius;
            int m_materialID;
    };

}
#endif // SPHERE_H_
