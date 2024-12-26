#ifndef METALLIC_H_
#define METALLIC_H_

#include "Material.h"

namespace Rye {
    class MetallicBSDF : public Material {
        public:
            MetallicBSDF() {}
            MetallicBSDF(glm::vec4 color) : m_color(color) {}

            bool BSDF(const glm::vec4& inRay, HitData& hit, glm::vec4& scatterRay) override;
            bool Absorb(const glm::vec4& inRay, HitData& hit) override;
            bool DrawAttributes() override;
            std::string GetName() override;

        private:
            glm::vec4 m_color = glm::vec4(0.9,0.9,0.9,1);
            float m_roughness = 0;
    };

}


#endif // METALLIC_H_
