#ifndef GLASS_H_
#define GLASS_H_

#include "Material.h"

namespace Rye {
    class GlassBSDf : public Material {
        public:
            bool BSDF(const glm::vec4& inRay, HitData& hit, glm::vec4& scatterRay) override
            {
                float eta = 1/m_IoR;
                float at = 1;

                hit.normal += random_on_sphere(hit.seed) * m_roughness;
                hit.normal = glm::normalize(hit.normal);

                if (hit.inside)
                {
                    eta = 1/eta;
                    hit.normal *= -1;
                }

                scatterRay = glm::refract(inRay, hit.normal, eta);
                bool reflect = glm::dot(scatterRay, scatterRay) < 0;

                reflect |= Fresnel(inRay, hit.normal, eta) > random_float(hit.seed);

                if (reflect)
                    scatterRay = glm::reflect(inRay, hit.normal);

                return true;
            }

            bool Absorb(const glm::vec4& inRay, HitData& hit) override
            {
                hit.color = glm::vec4(1);

                if (hit.inside)
                    hit.color *= glm::exp((m_color-1.0f)*hit.distance);

                return true;
            }

            bool DrawAttributes() override
            {
                ImGui::SetNextItemOpen(true, ImGuiCond_Once);
                if (ImGui::TreeNode("Glass BSDF"))
                {
                    ImGui::ColorEdit3("Color", glm::value_ptr(m_color), ImGuiColorEditFlags_Float);
                    ImGui::DragFloat("IoR", &m_IoR, 0.002f, 0.0f);
                    ImGui::DragFloat("Roughness", &m_roughness, 0.01f, 0, 1);
                    ImGui::TreePop();
                }
                return true;
            }


        private:
            glm::vec4 m_color = glm::vec4(1);
            float m_IoR = 1.5f;
            float m_roughness = 0;

    };
    
}

#endif // GLASS_H_
