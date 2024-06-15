#ifndef SPHERE_H_
#define SPHERE_H_

#include "Object.h"

namespace Rye {
    class Sphere : public Object {
        public:
            Sphere(glm::vec4 position, float radius, std::shared_ptr<Material> material)
                : m_position(position), m_radius(radius), m_material(material) {}

            bool Hit(const Ray &ray, HitData& hit) const override;
            bool DrawAttributes() override;

        protected:
            glm::vec4 m_position;
            float m_radius;
            std::shared_ptr<Material> m_material;
    };

}
#endif // SPHERE_H_
