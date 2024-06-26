#ifndef GLOSSY_H
#define GLOSSY_H

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

namespace Rye {
    class HitData;

}

namespace Rye::Materials {
    class Glossy {
        public:
            Glossy(glm::vec3 color)
                : color(color)
            {}

            bool BSDF(const glm::vec3& inRay, HitData& hit, glm::vec3& scatterRay) const;
            void Color(const glm::vec3& inRay, HitData& hit) const;
            static bool IsDoubleSided() { return false; }

        public:
            glm::vec3 color = glm::vec3(1.0f);
            float roughness = 0.0f;
            float specularity = 0.2f;

        private:
            mutable bool m_isSpecular = false;

    };
}

#endif // GLOSSY_H
