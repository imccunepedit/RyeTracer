#ifndef LAMBERTIAN_H_
#define LAMBERTIAN_H_

#include "Material.h"

namespace Rye {
    class LambertianBSDF : public Material {
        public:
            bool BSDF(const glm::vec4& inRay, HitData& hit, glm::vec4& scatterRay) override
            {
                scatterRay = glm::normalize(hit.normal + random_on_sphere(hit.seed)); //TODO replace 1 with seed
                return true;
            }

            bool Absorb(const glm::vec4& inRay, HitData& hit) override
            {
                hit.color = m_color;
                return true;
            }

            bool DrawAttributes() override
            {
                ImGui::ColorEdit3("Color", glm::value_ptr(m_color), ImGuiColorEditFlags_Float);
                return true;
            }

            std::string GetName() override
            {
                return "Diffuse BSDF";
            }

        private:
            glm::vec4 m_color = glm::vec4(0.5,0.5,0.5,1);

    };
}

#endif // LAMBERTIAN_H_
