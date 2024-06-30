#include "Objects/Quad.h"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "Renderer/Ray.h"

using namespace Rye::Objects;

bool Quad::Hit(const Ray& ray, HitData& hit, float t_min, bool doubleSided) const
{
    if (!m_plane.Hit(ray, hit, t_min, doubleSided))
        return false;

    glm::vec3 intersectionWorldSpace = hit.point;
    glm::vec3 intersectionPlanarWorldSpace = intersectionWorldSpace - m_position;

    glm::vec2 intersectionPlanarSpace;
    intersectionPlanarSpace.x = glm::dot(glm::vec3(m_w), glm::cross(intersectionPlanarWorldSpace, glm::vec3(m_v)));
    intersectionPlanarSpace.y = glm::dot(glm::vec3(m_w), glm::cross(glm::vec3(m_u), intersectionPlanarWorldSpace));

    if (intersectionPlanarSpace.x < 0.0f || intersectionPlanarSpace.x > 1.0f || intersectionPlanarSpace.y < 0.0f || intersectionPlanarSpace.y > 1.0f)
        return false;

    hit.materialID = m_materialID;

    return true;
}

Quad::Quad(const glm::vec3 position, const glm::vec3 u, const glm::vec3 v, int materialID)
    : m_position(position), m_u(u), m_v(v), m_materialID(materialID)
{
    glm::vec3 n = glm::cross(u, v);
    m_w = n / glm::dot(n,n);
    m_plane = Plane(glm::normalize(n), m_position);
}

// Quad::Quad(const glm::vec3 position, const glm::vec3 normal, const glm::vec2 size, int materialID)
//     : m_position(position), m_plane(normal, position), m_materialID(materialID)
// {

//     glm::vec3 n = glm::cross(u, v);
//     m_w = n / glm::dot(n,n);
// }
