#ifndef OBJECT_H_
#define OBJECT_H_

#include <variant>

#include <glm/vec3.hpp>

#include "Objects/Sphere.h"
#include "Objects/Quad.h"
#include "Objects/Plane.h"


namespace Rye::Assets {
    // https://www.cppstories.com/2018/09/visit-variants/
    template<class... Ts> struct overload : Ts... { using Ts::operator()...; };
    template<class... Ts> overload(Ts...) -> overload<Ts...>; // line not needed in C++20...

    using ObjectTypes = std::variant<Rye::Assets::Sphere,
                                     Rye::Assets::Plane,
                                     Rye::Assets::Quad>;

    class Object
    {
        public:
            Object(ObjectTypes o)
                : m_object(o)
            {}

            bool Hit(const Ray& ray, HitData& hit, float t_min) const
            {
                return std::visit(overload{[&] (const auto object) { return object.Hit(ray, hit, t_min); }, }, m_object);
            }

        private:
            ObjectTypes m_object;
    };
}

#endif // OBJECT_H_
