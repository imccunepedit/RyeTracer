#include "Quad.h"

#include <glm/geometric.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui.h"

using namespace Rye;

Quad::Quad(const glm::vec4 position, const glm::vec4 u, const glm::vec4 v, std::shared_ptr<Material> material)
    : m_position(position), m_u(u), m_v(v), m_material(material)
{
    glm::vec4 n = glm::vec4(glm::cross(glm::vec3(u), glm::vec3(v)), 0);
    m_w = n / glm::dot(n,n);
    m_normal = glm::normalize(n);
    m_planeOffset = glm::dot(m_position, m_normal);
}

bool Quad::Hit(const Ray &ray, HitData &hit) const
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

    glm::vec4 intersectionPoint = ray.at(t);

    // check if we intersect our quad
    glm::vec3 hitPointDir = intersectionPoint - m_position;

    float side = glm::dot(glm::vec3(m_w), glm::cross(hitPointDir, glm::vec3(m_v)));
    if (side < 0 || side > 1)
        return false;

    side = glm::dot(glm::vec3(m_w), glm::cross(glm::vec3(m_u), hitPointDir));
    if (side < 0 || side > 1)
        return false;

    hit.point = intersectionPoint;
    hit.front = a < 0;
    hit.distance = t;
    hit.normal = m_normal;
    hit.material = m_material;

    return true;
}


bool Quad::DrawAttributes()
{
    return false;
}
