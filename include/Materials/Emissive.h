#ifndef EMISSIVE_H
#define EMISSIVE_H

#include <glm/vec3.hpp>

namespace Rye {
    class HitData;
}
namespace Rye::Materials {
    class Emissive
    {
        public:
            Emissive() {}
            Emissive(float strength)
                : emissiveStrength(strength)
            {}

            bool BSDF(const glm::vec3& inRay, HitData& hit, glm::vec3& scatterRay) const { return false; }

            void Color(const glm::vec3& inRay, HitData& hit) const;
            static bool IsDoubleSided() { return false; }

        public:
            glm::vec3 color = glm::vec3(1.0f);
            float emissiveStrength = 4.0f;
    };
}


#endif // EMISSIVE_H
