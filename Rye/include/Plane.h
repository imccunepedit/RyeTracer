#ifndef PLANE_H_
#define PLANE_H_

#include "Object.h"

#include <glm/vec2.hpp>

namespace Rye {
    class Plane : public Object {
        public:
            Plane(const glm::vec4 position, const glm::vec4 u, const glm::vec4 v, std::shared_ptr<Material> material);

            bool Hit(const Ray &ray, HitData& hit) const override;
            bool DrawAttributes() override;

        protected:
            virtual bool InsideBounds(glm::vec2 planarCoord) const { return true; }

        protected:
            glm::vec4 m_position;
            glm::vec4 m_u, m_v, m_w;

            glm::vec4 m_normal;
            float m_planeOffset;

            std::shared_ptr<Material> m_material;
    };

}
#endif // PLANE_H_
