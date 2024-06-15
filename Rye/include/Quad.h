#ifndef QUAD_H_
#define QUAD_H_

#include "Plane.h"

namespace Rye {
    class Quad : public Plane {
        public:
            Quad(const glm::vec4 position, const glm::vec4 u, const glm::vec4 v, std::shared_ptr<Material> material);
            bool DrawAttributes() override;

        protected:
            bool InsideBounds(glm::vec2 planarCoord) const override;
        //     bool Hit(const Ray &ray, HitData& hit) const override;
        //     bool DrawAttributes() override;

        // protected:
        //     glm::vec4 m_position;
        //     glm::vec4 m_u, m_v, m_w;

        //     glm::vec4 m_normal;
        //     float m_planeOffset;

        //     std::shared_ptr<Material> m_material;
    };

}

#endif // QUAD_H_
