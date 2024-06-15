#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <string>

#include "imgui.h"

#include <glm/geometric.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Ray.h"
#include "Utils.h"
#include "HitData.h"


namespace Rye {
    class Material {
        public:
            virtual bool BSDF(const glm::vec4& inRay, HitData& hit, glm::vec4& scatterRay) { return false; }

            virtual bool Absorb(const glm::vec4& inRay, HitData& hit) { return false; } // technically emitting and being absorbed into camera but we are being backwards

            virtual bool DrawAttributes() { return false; }
            virtual std::string GetName() = 0;

        public:
            bool doubleSided = false;
        protected:
            float Fresnel(glm::vec4 I, glm::vec4 N, float n1)
            {
                float n2 = 1;
                float c1 = glm::dot(I,-N);
#ifndef SCHLICK
                float c2 = sqrtf(1 - n1*n1/(n2*n2) * (1- c1*c1));
                float Rs = (n1*c1 - n2*c2) / (n1*c1 + n2*c2);
                float Rp = (n1*c2 - n2*c1) / (n1*c2 + n2*c1);
                return 0.5 * (Rs*Rs + Rp*Rp);
#else
                float n12 = n1-n2;
                float R0 = n12 / (n1+n2);
                R0 *= R0;
                return R0 + (1-R0)*pow((1 - c1),5);
#endif
            }
    };

    class LambertianBSDF : public Material {
        public:
            LambertianBSDF() {}
            LambertianBSDF(glm::vec4 color) : m_color(color) {}
            bool BSDF(const glm::vec4& inRay, HitData& hit, glm::vec4& scatterRay) override;
            bool Absorb(const glm::vec4& inRay, HitData& hit) override;
            bool DrawAttributes() override;
            std::string GetName() override;

        private:
            glm::vec4 m_color = glm::vec4(0.5,0.5,0.5,1);

    };

    class SpecularBSDF : public Material {
        public:
            bool BSDF(const glm::vec4& inRay, HitData& hit, glm::vec4& scatterRay) override;
            bool Absorb(const glm::vec4& inRay, HitData& hit) override;
            bool DrawAttributes() override;
            std::string GetName() override;

        private:
            glm::vec4 m_color = glm::vec4(1);
            float m_roughness = 0;
    };


    class GlossyBSDF : public Material {
        public:
            bool BSDF(const glm::vec4& inRay, HitData& hit, glm::vec4& scatterRay) override;
            bool Absorb(const glm::vec4& inRay, HitData& hit) override;
            bool DrawAttributes() override;
            std::string GetName() override;

        private:
            LambertianBSDF m_diffuse;
            SpecularBSDF m_spec;
            float m_specularProb = 0.8;

    };


    class GlassBSDF : public Material {
        public:
            bool BSDF(const glm::vec4& inRay, HitData& hit, glm::vec4& scatterRay) override;
            bool Absorb(const glm::vec4& inRay, HitData& hit) override;
            bool DrawAttributes() override;
            std::string GetName() override;

        public:
            bool doubleSided = true;
        private:
            glm::vec4 m_color = glm::vec4(1);
            float m_indexOfRefraction = 1.5;
            float m_roughness = 0;
    };


    class MetallicBSDF : public Material {
        public:
            MetallicBSDF() {}
            MetallicBSDF(glm::vec4 color) : m_color(color) {}

            bool BSDF(const glm::vec4& inRay, HitData& hit, glm::vec4& scatterRay) override;
            bool Absorb(const glm::vec4& inRay, HitData& hit) override;
            bool DrawAttributes() override;
            std::string GetName() override;

        private:
            glm::vec4 m_color = glm::vec4(0.9,0.9,0.9,1);
            float m_roughness = 0;
    };

    class Emission : public Material {
        public:
            Emission() {};
            Emission(float strength) : m_strength(strength) {}

            bool Absorb(const glm::vec4& inRay, HitData& hit) override;
            bool DrawAttributes() override;
            std::string GetName() override;

        private:
            glm::vec4 m_color = glm::vec4(1.0,0.9,0.8,1);
            float m_strength = 4;
    };

}

#endif // MATERIAL_H_
