#include "Objects/AABB.h"

#include <glm/geometric.hpp>
#include <glm/vector_relational.hpp>

#include <Utils/Log.h>

#include "Renderer/Ray.h"

using namespace Rye::Objects;

AABB::AABB(glm::vec3 min, glm::vec3 max, int materialID)
    : m_min(min), m_max(max), m_materialID(materialID)
{

}



bool AABB::Hit(const Ray& ray, HitData& hit, float t_min) const
{
    glm::vec3 invRayDir = 1.0f / ray.direction;

    glm::vec3 t0 = (m_min - ray.origin) * invRayDir;
    glm::vec3 t1 = (m_max - ray.origin) * invRayDir;

    glm::vec3 n0 = glm::vec3(-1);

    if (t1.x < t0.x)
    {
      std::swap(t0.x, t1.x);
      n0.x *= -1;
    }
    if (t1.y < t0.y)
    {
      std::swap(t0.y, t1.y);
      n0.y *= -1;
    }
    if (t1.z < t0.z)
    {
      std::swap(t0.z, t1.z);
      n0.z *= -1;
    }

    float tf = glm::min(glm::min(glm::max(t0.x, t1.x), glm::max(t0.y, t1.y)), glm::max(t0.z, t1.z));
    float tn = glm::max(glm::max(glm::min(t0.x, t1.x), glm::min(t0.y, t1.y)), glm::min(t0.z, t1.z));

    // we didn't hit the box
    if (tf < tn)
        return false;

    float t = tn;
    // our closes hit is too close/ behind us
    if (t < t_min)
    {
        // our farther hit is also behind us
        if (tf < t_min)
            return false;

        hit.front = false;
        t = tf;
        t0 = t1;
        n0 *= -1;
    }


    if (t0.y == t)
        hit.normal = glm::vec3(0,1,0) * n0.y;
    else if (t0.x == t)
        hit.normal = glm::vec3(1,0,0) * n0.x;
    else if (t0.z == t)
        hit.normal = glm::vec3(0,0,1) * n0.z;

    hit.distance = t;
    hit.point = ray.at(t);
    hit.materialID = m_materialID;
    return true;
}
