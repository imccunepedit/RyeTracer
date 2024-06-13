#ifndef LAMBERTIAN_H_
#define LAMBERTIAN_H_

#include "Material.h"

namespace Barley {
    class LambertianBSDF : public Material {
        public:
            bool BSDF(const Ray& inRay, HitData& hit, Ray& scatterRay) override
            {
                uint32_t seed = inRay.seed;
                scatterRay.direction = glm::normalize(hit.normal + random_on_sphere(seed));

                scatterRay.origin = hit.point;
                scatterRay.seed = seed;
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
            glm::vec4 m_color = glm::vec4(0.5f);

    };
}

#endif // LAMBERTIAN_H_
