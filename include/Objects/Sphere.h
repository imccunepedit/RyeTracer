#ifndef SPHERE_H
#define SPHERE_H

#include <glm/vec3.hpp>


namespace Rye {
    class Ray;
    class HitData;
}

namespace Rye::Objects {
    class Sphere
    {
        public:
            Sphere(glm::vec3 postion, float radius, int materialID)
                : m_position(postion), m_radius(radius), m_materialID(materialID)
            {}

            bool Hit(const Ray& ray, HitData& hit, float t_min) const;

        private:
            int m_materialID = 0;
            glm::vec3 m_position;
            float m_radius;

    };
}

#endif /* SPHERE_H */
