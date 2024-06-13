#ifndef SPECULAR_H_
#define SPECULAR_H_

#include "Material.h"

namespace Barley {

    class SpecularBSDF : public Material {
        public:
            bool BSDF(const Ray& inRay, HitData& hit, Ray& scatterRay) override
            {
                uint32_t seed = inRay.seed;

                hit.color = m_color;
                scatterRay.direction = glm::normalize(glm::reflect(inRay.direction, hit.normal) + random_on_sphere(seed) * m_roughness);

                scatterRay.origin = hit.point;
                scatterRay.seed = seed;
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
