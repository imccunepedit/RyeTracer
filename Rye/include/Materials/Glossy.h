#ifndef GLOSSY_H_
#define GLOSSY_H_

#include "Material.h"
#include "Materials/Lambertian.h"
#include "Materials/Specular.h"

namespace Rye {
    class GlossyBSDF : public Material {
        public:
            bool BSDF(const glm::vec4& inRay, HitData& hit, glm::vec4& scatterRay) override;
            bool Absorb(const glm::vec4& inRay, HitData& hit) override;
            bool DrawAttributes() override;
            std::string GetName() override;

        private:
            LambertianBSDF m_diffuse;
            SpecularBSDF m_spec;
            float m_specularity = 0.2;
    };
}


#endif // GLOSSY_H_
