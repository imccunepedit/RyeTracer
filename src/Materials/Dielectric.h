#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>


namespace Rye {
    class HitData;
}

namespace Rye::Materials {
    class Dielectric {
        public:
            Dielectric(glm::vec3 color, float IoR)
                : color(color), indexOfRefraction(IoR)
            {}

            bool BSDF(const glm::vec3& inRay, HitData& hit, glm::vec3& scatterRay) const;
            void Color(const glm::vec3& inRay, HitData& hit) const;
            bool IsDoubleSided() const { return true; }

        public:
            glm::vec3 color;
            float indexOfRefraction;

            float roughness = 0.0f;


    };
}

#endif // CONDUCTOR_H
