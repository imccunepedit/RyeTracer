#ifndef METALLIC_H_
#define METALLIC_H_

#include "Material.h"

namespace Rye {

    class MetallicBSDF : public Material {
        public:
            MetallicBSDF() {}
            MetallicBSDF(glm::vec4 color) : m_color(color) {}
            bool BSDF(const glm::vec4 &inRay, HitData &hit, glm::vec4 &scatterRay) override {
                uint32_t seed = 1;
                scatterRay = glm::reflect(inRay, hit.normal) + random_on_sphere(seed) * m_roughness;

                // scatterRay.seed = seed;
                float f = Fresnel(inRay, hit.normal, 0.27732f);
                hit.color = (1-f) * m_color + f * glm::vec4(1);
                return true;
            }

            bool DrawAttributes() override
            {
                ImGui::ColorEdit3("Color", glm::value_ptr(m_color), ImGuiColorEditFlags_Float);
                ImGui::DragFloat("Roughness", &m_roughness);
                return true;
            }

            std::string GetName() override
            {
                return "Metallic BSDF";
            }

        private:
            glm::vec4 m_color = glm::vec4(0.9f);
            float m_roughness = 0;
    };


}

#endif // METALLIC_H_
