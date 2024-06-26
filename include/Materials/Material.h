#ifndef MATERIAL_H
#define MATERIAL_H

#include <variant>

#include "Materials/Lambertian.h"
#include "Materials/Conductor.h"
#include "Materials/Dielectric.h"
#include "Materials/Glossy.h"
#include "Materials/Emissive.h"


namespace Rye::Materials {
    // https://www.cppstories.com/2018/09/visit-variants/
    template<class... Ts> struct overload : Ts... { using Ts::operator()...; };
    template<class... Ts> overload(Ts...) -> overload<Ts...>; // line not needed in C++20...

    using MaterialTypes = std::variant<Rye::Materials::Lambertian,
                                       Rye::Materials::Conductor,
                                       Rye::Materials::Dielectric,
                                       Rye::Materials::Glossy,
                                       Rye::Materials::Emissive>;

    class Material
    {
        public:
            Material(MaterialTypes m)
                : m_material(m)
            {}

            bool BSDF(const glm::vec3& inRay, HitData& hit, glm::vec3& scatterRay) const
            {
                return std::visit(overload{[&] (const auto material) { return material.BSDF(inRay, hit, scatterRay); }, }, m_material);
            }
            void Color(const glm::vec3& inRay, HitData& hit) const
            {
                return std::visit(overload{[&] (const auto material) { return material.Color(inRay, hit); }, }, m_material);
            }
            bool IsDoubleSided() const
            {
                return std::visit(overload{[&] (const auto material) { return material.IsDoubleSided(); }, }, m_material);
            }

        private:
            MaterialTypes m_material;

    };
}

#endif // MATERIAL_H
