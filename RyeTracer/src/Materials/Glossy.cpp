#ifndef GLOSSY_H_
#define GLOSSY_H_

#include "Material.h"

#include "Lambertian.h"
#include "Specular.h"

namespace Rye {
    class GlossyBSDF : public Material {
        public:
            bool BSDF(const glm::vec4& inRay, HitData& hit, glm::vec4& scatterRay) override
            {
                if (random_float(hit.seed) > m_specularProb)
                {
                    m_diffuse.BSDF(inRay, hit, scatterRay);
                    return true;
                }
                m_spec.BSDF(inRay, hit, scatterRay);
                return true;
            }

            bool Absorb(const glm::vec4& inRay, HitData& hit) override
            {
                hit.color = glm::vec4(1);
                return true;
            }

            bool DrawAttributes() override
            {
                m_diffuse.DrawAttributes();
                m_spec.DrawAttributes();
                ImGui::DragFloat("Specular probability", &m_specularProb, 0.01f, 0,1);
                return true;
            }

            std::string GetName() override
            {
                return "Glossy BSDF";
            }

        private:
            LambertianBSDF m_diffuse;
            SpecularBSDF m_spec;
            float m_specularProb = 0.8;

    };
}


#endif // GLOSSY_H_
