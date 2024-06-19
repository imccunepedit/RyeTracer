#ifndef OBJECT_H_
#define OBJECT_H_

#include <glm/vec4.hpp>

namespace Rye {
    class Ray;
    class HitData;

    class Object {
        public:
            virtual bool Hit(const Ray& ray, HitData& hit) const { return false; }

        public:
            glm::vec4 m_position = glm::vec4(0);
            int m_materialID = 0;
    };
}

#endif // OBJECT_H_
