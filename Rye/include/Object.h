#ifndef OBJECT_H_
#define OBJECT_H_

#include <glm/vec4.hpp>

#include "Transform.h"

namespace Rye {
    class Ray;
    class HitData;

    class Object {
        public:
            enum Type {Sphere, Quad};
        public:
            Object(Type type)
                : objectType(type) {}
            Object(Type type, Transform transform, int materialID)
                : objectType(type), transform(transform), m_materialID(materialID) {}

            bool Hit(const Ray& ray, HitData& hit) const;
            bool SphereHit(const Ray& ray, HitData& hit) const;
            bool QuadHit(const Ray& ray, HitData& hit) const;

        public:
            Type objectType;
            Transform transform = Transform();
            int m_materialID = 0;
    };
}

#endif // OBJECT_H_
