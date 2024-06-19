#ifndef PLANE_H_
#define PLANE_H_

#include <memory>

#include "Object.h"

#include <glm/vec2.hpp>

namespace Rye {
    class Material;

    class Plane : public Object {
        public:
            Plane(const glm::vec4 position, const glm::vec4 u, const glm::vec4 v, int materialID);
            bool Hit(const Ray &ray, HitData& hit) const override;

        protected:
            virtual bool InsideBounds(glm::vec2 planarCoord) const { return true; }

        public:
            glm::vec4 m_position;
            glm::vec4 m_u, m_v, m_w;

            glm::vec4 m_normal;
            float m_planeOffset;

            int m_materialID;
    };

}
#endif // PLANE_H_
