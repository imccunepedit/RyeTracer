#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <string>

#include <glm/vec4.hpp>
#include <glm/geometric.hpp>


namespace Rye {
    class HitData;

    class Material {
        public:
            virtual bool BSDF(const glm::vec4& inRay, HitData& hit, glm::vec4& scatterRay) { return false; }
            virtual bool Absorb(const glm::vec4& inRay, HitData& hit) { return false; }

            virtual bool DrawAttributes() { return false; }
            virtual std::string GetName() = 0;

        public:
            bool doubleSided = false;
    };
}

#endif // MATERIAL_H_
