#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>


namespace Rye {
    class HitData;

    class Material {
        public:
            enum Type {Lambertian,
                       Conductor,
                       Dielectric,
                       Glossy,
                       Emissive};

        public:
            Material(Type type)
                : materialType(type) {}
            Material(Type type, glm::vec3 color)
                : materialType(type), color(color) {}
            Material(Type type, glm::vec3 color, float roughness)
                : materialType(type), color(color), roughness(roughness) {}
            Material(Type type, glm::vec3 color, float roughness, float ior)
                : materialType(type), color(color), roughness(roughness), indexOfRefraction(ior) {}

        public:
            bool BSDF(const glm::vec3& inRay, HitData& hit, glm::vec3& scatterRay) const;
            void Color(const glm::vec3& inRay, HitData& hit);

        private:
            bool DielectricBSDF(const glm::vec3& inRay, HitData& hit, glm::vec3& scatterRay) const;
            bool GlossyBSDF(const glm::vec3& inRay, HitData& hit, glm::vec3& scatterRay) const;

        public:
            int materialType;
            glm::vec3 color = glm::vec3(0.5f,0.5f,0.5f);
            float roughness = 0.0f;

            bool doubleSided = false;
            float specularity = 0.2f;
            float indexOfRefraction = 1.5f;
            float emissiveStrength = 4.0f;

        private:
             bool m_isSpecular = false;
    };
}

#endif // MATERIAL_H_
