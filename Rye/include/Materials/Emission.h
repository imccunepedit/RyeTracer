#ifndef EMISSION_H_
#define EMISSION_H_

#include "Material.h"

namespace Rye {
    class Emission : public Material {
        public:
            Emission() {};
            Emission(float strength) : m_strength(strength) {}

            bool Absorb(const glm::vec4& inRay, HitData& hit) override;
            bool DrawAttributes() override;
            std::string GetName() override;

        private:
            glm::vec4 m_color = glm::vec4(1.0,0.9,0.8,1);
            float m_strength = 4;
    };
}


#endif // EMISSION_H_
