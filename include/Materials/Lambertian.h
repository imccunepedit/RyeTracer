#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>


namespace Rye {
    class HitData;
}

namespace Rye::Materials {

    class Lambertian {
        public:
            Lambertian() {}
            Lambertian(glm::vec3 color)
                : color(color)
            {}

        public:
            bool BSDF(const glm::vec3& inRay, HitData& hit, glm::vec3& scatterRay) const;
            void Color(const glm::vec3& inRay, HitData& hit) const;
            static bool IsDoubleSided() { return false; }

        public:
            glm::vec3 color = glm::vec3(0.5f);
    };
}

#endif // LAMBERTIAN_H
