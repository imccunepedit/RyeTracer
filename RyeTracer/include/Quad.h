#ifndef QUAD_H_
#define QUAD_H_

#include "Object.h"

#include <glm/vec4.hpp>

#include "Ray.h"
#include "HitData.h"

namespace Rye {
    class Quad : public Object {
        public:
            Quad(const glm::vec4 position, const glm::vec4 u, const glm::vec4 v, std::shared_ptr<Material> material);

            bool Hit(const Ray &ray, HitData& hit) const override;
            bool DrawAttributes() override;

        protected:
            glm::vec4 m_position;
            glm::vec4 m_u, m_v, m_w;

            glm::vec4 m_normal;
            float m_planeOffset;

            std::shared_ptr<Material> m_material;
    };

}
#endif // QUAD_H_
