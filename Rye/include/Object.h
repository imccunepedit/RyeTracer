#ifndef OBJECT_H_
#define OBJECT_H_

#include <glm/vec4.hpp>

#include "Transform.h"

namespace Rye {
    class Ray;
    class HitData;

    class Object {
        public:
            enum Type {Sphere, Quad, AABB};
        public:
            Object(Type type, Transform tf, int materialID);

            bool Hit(const Ray& ray, HitData& hit) const;
            bool SphereHit(const Ray& ray, HitData& hit) const;
            bool QuadHit(const Ray& ray, HitData& hit) const;
            bool AABBHit(const Ray& ray, HitData& hit) const;

        public:
            Type objectType;
            Transform transform = Transform();
            int m_materialID = 0;

        private:
            glm::vec3 m_planeNormal = glm::vec3(0,0,1);
            glm::vec3 m_u = glm::vec3(1,0,0);
            glm::vec3 m_v = glm::vec3(0,1,0);
            glm::vec3 m_w = glm::vec3(0,0,1);
            float m_planeOffset = 1.0f;
    };
}

#endif // OBJECT_H_
