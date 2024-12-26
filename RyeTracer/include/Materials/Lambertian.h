#ifndef LAMBERTIAN_H_
#define LAMBERTIAN_H_

#include "Material.h"

namespace Rye {
    class LambertianBSDF : public Material {
        public:
            LambertianBSDF() {}
            LambertianBSDF(glm::vec4 color) : m_color(color) {}
            bool BSDF(const glm::vec4& inRay, HitData& hit, glm::vec4& scatterRay) override;
            bool Absorb(const glm::vec4& inRay, HitData& hit) override;
            bool DrawAttributes() override;
            std::string GetName() override;

        private:
            glm::vec4 m_color = glm::vec4(0.5,0.5,0.5,1);

    };
}
#endif // LAMBERTIAN_H_
