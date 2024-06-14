#ifndef GLASS_H_
#define GLASS_H_

#include "Material.h"


namespace Barley {

    class GlassBSDf : public Material {
        public:
            bool BSDF(const Ray& inRay, HitData& hit, Ray& scatterRay) override
            {
                uint32_t seed = inRay.seed;
                float eta = 1/m_IoR;
                float at = 1;

                hit.normal += random_on_sphere(seed) * m_roughness;
                hit.normal = glm::normalize(hit.normal);

                hit.color = glm::vec4(1);
                if (hit.inside)
                {
                    eta = 1/eta;
                    hit.normal *= -1;
                    hit.color *= glm::exp((m_color-1.0f)*hit.distance);
                }

                scatterRay.direction = glm::refract(inRay.direction, hit.normal, eta);
                bool reflect = glm::dot(scatterRay.direction, scatterRay.direction) < 0.1;

                reflect |= Fresnel(inRay.direction, hit.normal, eta) > Barley::random_float(seed);

                if (reflect)
                    scatterRay.direction = glm::reflect(inRay.direction, hit.normal);


                scatterRay.origin = hit.point;
                scatterRay.seed = seed;
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
