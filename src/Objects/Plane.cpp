#include "Objects/Plane.h"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "Renderer/Ray.h"

using namespace Rye::Objects;


bool Plane::Hit(const Ray& ray, HitData& hit, float t_min) const
{
    float a = glm::dot(m_normal, ray.direction);

    // currently quads are infinetly thin so theres no reason to intersect their back.
    // if th ra direction and the plane normal don't point against each other then we would only hit the back
    if (a > 0)
        return false;

    float t = (m_planeOffset - glm::dot(m_normal, ray.origin)) / a;

    if (t < t_min)
        return false;

    hit.point = ray.at(t);
    hit.distance = t;
    hit.normal = m_normal;
    hit.materialID = m_materialID;

    return true;
}


Plane::Plane(const glm::vec3 normal, const glm::vec3 point)
    : m_normal(normal), m_planeOffset(glm::dot(normal, point))
{

}
