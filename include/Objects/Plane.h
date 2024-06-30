#ifndef PLANE_H
#define PLANE_H

#include <glm/vec3.hpp>

namespace Rye {
    class Ray;
    class HitData;
}

namespace Rye::Objects {
    class Plane
    {
        public:
            Plane() {}

            Plane(const glm::vec3 normal, const glm::vec3 point);
            bool Hit(const Ray& ray, HitData& hit, float t_min, bool doubleSided = false) const;
        private:
            glm::vec3 m_normal;
            float m_planeOffset;

            int m_materialID = 0;

    };
}

#endif /* PLANE_H */
