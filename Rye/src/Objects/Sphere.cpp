#include "Objects/Sphere.h"

#include <glm/geometric.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Ray.h"

using namespace Rye;

#if 0
bool Sphere::Hit(const Ray &ray, HitData& hit) const {
    // calculate a b and c for the quadratic fomula
    // see docs/raytracing.org for explanation
    //
    // since the ray direction should be normalized a should always be equal to 1
    // float a = glm::dot(ray.direction, ray.direction);
    float b = 2.0 * glm::dot(ray.direction, ray.origin - m_position);
    float c = glm::dot(m_position - ray.origin, m_position - ray.origin) - m_radius * m_radius;

    // calculate the discriminant
    float discriminant = b*b - 4*c;

    // if the disciminant is negative there wasn't a hit and as far as the sphere knows
    if (discriminant < 0) {
        return false;
    }


    float min_t = 0.001;
    // make sure that we only use rays that go away from the camera
    // we don't want to be able to see behind use
    float t = (-b - std::sqrt(discriminant)) * 0.5f;

    if (t < min_t)
    {
        // if the first t was negative that means that it hit something behind us, we can now check
        // if the second point is also behind us
        t = (-b + std::sqrt(discriminant)) * 0.5f;
        if (t < min_t)
            return false;
        // if the point isn't behind us we are inside the sphere so we tell our hit that.
        hit.front = false;
    }

    // otherwise calculate hit position
    hit.distance = t;
    hit.point = ray.at(t);
    hit.normal = (hit.point - m_position) / m_radius;
    hit.materialID = m_materialID;

    return true;

}



#endif
