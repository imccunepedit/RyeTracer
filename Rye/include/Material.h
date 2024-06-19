#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
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
            Material() = default;
            Material(Type type) : materialType(type) {}
            Material(Type type, glm::vec4 color) : materialType(type), color(color) {}
            Material(Type type, glm::vec4 color, float roughness) : materialType(type), color(color), roughness(roughness) {}

        public:
            bool BSDF(const glm::vec3& inRay, HitData& hit, glm::vec3& scatterRay);
            void Color(const glm::vec3& inRay, HitData& hit);

        private:
            bool DielectricBSDF(const glm::vec3& inRay, HitData& hit, glm::vec3& scatterRay);

        public:
            int materialType = Lambertian;
            glm::vec4 color = glm::vec4(0.5f,0.5f,0.5f,1.0f);
            float roughness = 0;

            bool doubleSided = false;
            float indexOfRefraction = 1.5f;
            float emissiveStrength = 4.0f;
    };
}

#endif // MATERIAL_H_
