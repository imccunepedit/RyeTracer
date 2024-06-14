#ifndef SPECULAR_H_
#define SPECULAR_H_

#include "Material.h"

namespace Rye {
    class SpecularBSDF : public Material {
        public:
            bool BSDF(const glm::vec4& inRay, HitData& hit, glm::vec4& scatterRay) override
            {
                uint32_t seed = 1;

                hit.color = m_color;
                scatterRay = glm::normalize(glm::reflect(inRay, hit.normal) + random_on_sphere(seed) * m_roughness);

                return true;
            }

            bool DrawAttributes() override
            {
                ImGui::PushID((int*) "specular");
                ImGui::ColorEdit3("Color", glm::value_ptr(m_color), ImGuiColorEditFlags_Float);
                ImGui::DragFloat("Roughness", &m_roughness, 0.01f, 0, 1);
                ImGui::PopID();
                return true;
            }

            std::string GetName() override
            {
                return "Specular BSDF";
            }


        private:
            glm::vec4 m_color = glm::vec4(1);
            float m_roughness = 0;

    };
}


#endif // SPECULAR_H_
