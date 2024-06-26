#ifndef AABB_H
#define AABB_H

#include <glm/vec3.hpp>

namespace Rye {
    class Ray;
    class HitData;

}


namespace Rye::Objects {
    class AABB
    {
        public:
            AABB(glm::vec3 min, glm::vec3 max, int materialID)
                : m_min(min), m_max(max), m_materialID(materialID)
            {}

            bool Hit(const Ray& ray, HitData& hit, float t_min) const;

        private:
            int m_materialID = 0;
            glm::vec3 m_min, m_max;
    };
}

#endif /* AABB_H */
