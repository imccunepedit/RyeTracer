#ifndef CONDUCTOR_H
#define CONDUCTOR_H

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>


namespace Rye {
    class HitData;
}

namespace Rye::Materials {
    class Conductor {
        public:
            Conductor(glm::vec3 color, float IoR)
                : color(color), indexOfRefraction(IoR)
            {}

            bool BSDF(const glm::vec3& inRay, HitData& hit, glm::vec3& scatterRay) const;
            void Color(const glm::vec3& inRay, HitData& hit) const;
            static bool IsDoubleSided() { return false; }

        public:
            glm::vec3 color = glm::vec3(1.0f);
            float roughness = 0.0f;

            float indexOfRefraction = 1.7f;

    };
}

#endif // CONDUCTOR_H
