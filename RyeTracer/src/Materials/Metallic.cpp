#ifndef METALLIC_H_
#define METALLIC_H_

#include "Material.h"

namespace Rye {

    class MetallicBSDF : public Material {
        public:
            MetallicBSDF() {}
            MetallicBSDF(glm::vec4 color) : m_color(color) {}
            bool BSDF(const glm::vec4& inRay, HitData& hit, glm::vec4& scatterRay) override {
                scatterRay = glm::reflect(inRay, hit.normal) + random_on_sphere(hit.seed) * m_roughness;
                return true;
            }

            bool Absorb(const glm::vec4& inRay, HitData& hit) override
            {
                float f = Fresnel(inRay, hit.normal, 0.2f);
                hit.color = (1-f) * m_color + f * glm::vec4(1);
                return true;
            }

            bool DrawAttributes() override
            {
                ImGui::ColorEdit3("Color", glm::value_ptr(m_color), ImGuiColorEditFlags_Float);
                ImGui::DragFloat("Roughness", &m_roughness,0.01,0,1);
                return true;
            }

            std::string GetName() override
            {
                return "Metallic BSDF";
            }

        private:
            glm::vec4 m_color = glm::vec4(1);
            float m_roughness = 0;
    };


}

#endif // METALLIC_H_
