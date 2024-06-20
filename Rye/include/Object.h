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
            // Object(glm::vec3 position, float radius, int materialID)
            //     : objectType(Sphere), transform(position, radius), m_materialID(materialID)
            // {

            // }

            // Object(glm::vec3 position, glm::vec3 u, glm::vec3 v, int materialID)
            //     : objectType(Quad), transform(position), m_u(u), m_v(v), m_materialID(materialID)
            // {
            //         glm::vec3 n = glm::cross(u, v);
            //         m_w = n / glm::dot(n,n);
            //         m_planeNormal = glm::normalize(n);
            //         m_planeOffset = glm::dot(transform.position, m_planeNormal);
            // }

            Object(Type type, Transform tf, int materialID)
                : objectType(type), transform(tf), m_materialID(materialID)
            {
                if (objectType == Quad)
                {
                    m_u = transform.matrix * glm::vec4(1,0,0,0);
                    m_v = transform.matrix * glm::vec4(0,1,0,0);
                    // m_u = transform.scale * glm::vec3(1,0,0);
                    // m_v = transform.scale * glm::vec3(0,1,0);
                    glm::vec3 n = glm::cross(m_u, m_v);
                    m_w = n/glm::dot(n,n);
                    m_planeNormal = glm::normalize(n);
                    m_planeOffset = glm::dot(transform.position, m_planeNormal);
                }
            }

            bool Hit(const Ray& ray, HitData& hit) const;
            bool SphereHit(const Ray& ray, HitData& hit) const;
            bool QuadHit(const Ray& ray, HitData& hit) const;

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
