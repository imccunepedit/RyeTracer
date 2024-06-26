#include "Objects/Sphere.h"

#include "Renderer/Ray.h"

using namespace Rye::Assets;

bool Sphere::Hit(const Ray& ray, HitData& hit, float t_min) const
{
    glm::vec3 oc = ray.origin - m_position;
    float b = glm::dot(ray.direction, oc);
    float c = glm::dot(oc, oc) - m_radius * m_radius;

    // calculate the discriminant
    float discriminant = b*b - c;

    // if the disciminant is negative there wasn't a hit and as far as the sphere knows
    if (discriminant < 0) {
        return false;
    }

    // make sure that we only use rays that go away from the camera
    // we don't want to be able to see behind use

    float t = (-b - std::sqrt(discriminant));
    if (t < t_min)
    {
        // if the first t was negative that means that it hit something behind us, we can now check
        // if the second point is also behind us
        t = (-b + std::sqrt(discriminant));
        if (t < t_min)
            return false;
        // if the point isn't behind us we are inside the sphere so we tell our hit that.
        hit.front = false;
        // Rye::log("inside");
    }

    // otherwise calculate hit position
    hit.distance = t;
    hit.point = ray.at(t);
    hit.normal = (hit.point - m_position) / m_radius;
    hit.materialID = m_materialID;

    return true;
}
