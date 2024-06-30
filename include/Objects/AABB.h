#ifndef AABB_H
#define AABB_H

#include <glm/vec3.hpp>

#include "Objects/Quad.h"

namespace Rye {
    class Ray;
    class HitData;

}


namespace Rye::Objects {
    class AABB
    {
        public:
            AABB(glm::vec3 min, glm::vec3 max, int materialID);

            bool Hit(const Ray& ray, HitData& hit, float t_min) const;

        private:
            int m_materialID = 0;
            Quad m_faces[6];
            // glm::vec3 m_min, m_max;
    };
}

#endif /* AABB_H */
