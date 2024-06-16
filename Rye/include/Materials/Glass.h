#ifndef GLASS_H_
#define GLASS_H_

#include "Material.h"

namespace Rye {
    class GlassBSDF : public Material {
        public:
            bool BSDF(const glm::vec4& inRay, HitData& hit, glm::vec4& scatterRay) override;
            bool Absorb(const glm::vec4& inRay, HitData& hit) override;
            bool DrawAttributes() override;
            std::string GetName() override;

        public:
            bool doubleSided = true;
        private:
            glm::vec4 m_color = glm::vec4(1);
            float m_indexOfRefraction = 1.5;
            float m_roughness = 0;
    };
}

#endif // GLASS_H_
