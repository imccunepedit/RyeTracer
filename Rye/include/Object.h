#ifndef OBJECT_H_
#define OBJECT_H_

#include <glm/vec4.hpp>

#include "Transform.h"

namespace Rye {
    class Ray;
    class HitData;

    class Object {
        enum Type {Sphere,
                   Quad};
        public:
            Object() = default;
            Object(Transform transform, int materialID) : transform(transform), m_materialID(materialID) {}

            bool Hit(const Ray& ray, HitData& hit) const;

        public:
            Transform transform = Transform(0);
            int m_materialID = 0;

    };
}

#endif // OBJECT_H_
