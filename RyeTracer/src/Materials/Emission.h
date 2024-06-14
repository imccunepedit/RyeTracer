#ifndef EMISSION_H_
#define EMISSION_H_

#include "Material.h"


namespace Rye {
    class Emission : public Material {
        public:
            Emission() {};
            Emission(glm::vec4 color, float strength) : m_color(color), m_strength(strength) {}
            bool Absorb(const glm::vec4& in_ray, HitData& hit) override
            {
                hit.color =  m_color * m_strength;
                return true;
            }

            bool DrawAttributes() override
            {
                ImGui::ColorEdit3("Color", glm::value_ptr(m_color), ImGuiColorEditFlags_Float);
                ImGui::DragFloat("Strength", &m_strength, 1.0f, 0.0f);
                return true;
            }

            std::string GetName() override
            {
                return "Emmisive";
            }

        private:
            glm::vec4 m_color = glm::vec4(1.0f, 0.9f, 0.8f, 1);
            float m_strength = 10.0f;
    };
}

#endif // EMISSION_H_
