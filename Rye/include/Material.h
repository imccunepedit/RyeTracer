#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <string>

#include <glm/vec4.hpp>
#include <glm/geometric.hpp>


namespace Rye {
    class HitData;


    class Material {
        public:
            enum Type {Lambertian,
                       Conductor,
                       Dielectric,
                       Emissive};

        public:
            Material() = default;
            Material(Type type) : materialType(type) {}
            Material(Type type, glm::vec4 color) : materialType(type), color(color) {}
            Material(Type type, glm::vec4 color, float roughness) : materialType(type), color(color), roughness(roughness) {}

        public:
            bool BSDF(const glm::vec4& inRay, HitData& hit, glm::vec4& scatterRay);
            void Color(const glm::vec4& inRay, HitData& hit);
            // bool DrawAttributes() { return false; }
            // std::string GetName();
        private:
            bool DielectricBSDF(const glm::vec4& inRay, HitData& hit, glm::vec4& scatterRay);

        public:
            int materialType = Lambertian;
            glm::vec4 color = glm::vec4(0.5f,0.5f,0.5f,1.0f);
            float roughness = 1;

            bool doubleSided = false;
            float indexOfRefraction = 1.5f;
            float emissiveStrength = 4.0f;
    };
}

#endif // MATERIAL_H_
