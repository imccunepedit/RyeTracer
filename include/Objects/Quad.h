#ifndef QUAD_H
#define QUAD_H

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "Plane.h"

namespace Rye {
    class Ray;
    class HitData;
}

namespace Rye::Assets {
    class Quad
    {
        public:
            Quad(const glm::vec3 position, const glm::vec3 u, const glm::vec3 v, int materialID);
            // Quad(const glm::vec3 position, const glm::vec3 normal, const glm::vec2 size, int materialID);
            bool Hit(const Ray& ray, HitData& hit, float t_min) const;

        private:
            glm::vec3 m_position;
            glm::vec3 m_u,m_v,m_w;
            Plane m_plane;
            int m_materialID = 0;
    };
}

#endif /* QUAD_H */
