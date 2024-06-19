#include "Objects/Plane.h"

#include <glm/geometric.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "Ray.h"

using namespace Rye;

Plane::Plane(const glm::vec4 position, const glm::vec4 u, const glm::vec4 v, int materialID)
    : m_position(position), m_u(u), m_v(v), m_materialID(materialID)
{
    glm::vec4 n = glm::vec4(glm::cross(glm::vec3(u), glm::vec3(v)), 0);
    m_w = n / glm::dot(n,n);
    m_normal = glm::normalize(n);
    m_planeOffset = glm::dot(m_position, m_normal);
}

bool Plane::Hit(const Ray &ray, HitData &hit) const
{
    float a = glm::dot(m_normal, ray.direction);

    if (std::abs(a) < 0.00001)
    {
        return false;
    }

    float t = (m_planeOffset - glm::dot(m_normal, ray.origin)) / a;

    float min_t = 0.0001;
    if (t < min_t)
        return false;

    glm::vec4 intersectionWorldSpace = ray.at(t);
    glm::vec3 intersectionPlanarWorldSpace = intersectionWorldSpace - m_position;

    glm::vec2 intersectionPlanarSpace;
    intersectionPlanarSpace.x = glm::dot(glm::vec3(m_w), glm::cross(intersectionPlanarWorldSpace, glm::vec3(m_v)));
    intersectionPlanarSpace.y = glm::dot(glm::vec3(m_w), glm::cross(glm::vec3(m_u), intersectionPlanarWorldSpace));

    if (!InsideBounds(intersectionPlanarSpace))
        return false;

    hit.point = intersectionWorldSpace;
    hit.front = a < 0;
    hit.distance = t;
    hit.normal = m_normal;
    hit.materialID = m_materialID;

    return true;
}

