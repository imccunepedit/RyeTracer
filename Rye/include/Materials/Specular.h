#ifndef SPECULAR_H_
#define SPECULAR_H_

#include "Material.h"

namespace Rye {
    class SpecularBSDF : public Material {
        public:
            bool BSDF(const glm::vec4& inRay, HitData& hit, glm::vec4& scatterRay) override;
            bool Absorb(const glm::vec4& inRay, HitData& hit) override;
            bool DrawAttributes() override;
            std::string GetName() override;

        private:
            glm::vec4 m_color = glm::vec4(1);
            float m_roughness = 0;
    };
}


#endif // SPECULAR_H_
