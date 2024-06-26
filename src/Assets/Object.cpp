#include "Assets/Object.h"

#include "Renderer/Ray.h"

using namespace Rye;

constexpr float epsilon = 0.0001f;

Object::Object(Type type, Transform tf, int materialID)
    : objectType(type), transform(tf), m_materialID(materialID)
{
    switch (objectType) {
        default:
            break;
        case Quad:
        {
            m_u = transform.matrix * glm::vec4(1, 0, 0, 0);
            m_v = transform.matrix * glm::vec4(0, 1, 0, 0);
            glm::vec3 n = glm::cross(m_u, m_v);
            m_w = n / glm::dot(n, n);
            m_planeNormal = glm::normalize(n);
            m_planeOffset = glm::dot(transform.position, m_planeNormal);
            break;
        }

        case AABB:
        {
            break;
        }
    }
}

bool Object::Hit(const Ray &ray, HitData& hit) const
{

    hit.materialID = m_materialID;

    switch (objectType) {
        case Sphere:
            return SphereHit(ray, hit);

        case Quad:
            return QuadHit(ray, hit);

        default:
            return false;
    }
}

bool Object::SphereHit(const Ray& ray, HitData& hit) const
{
    glm::vec3 oc = ray.origin - transform.position;
    float b = glm::dot(ray.direction, oc);
    float c = glm::dot(oc, oc) - transform.scale.x * transform.scale.x;

    // calculate the discriminant
    float discriminant = b*b - c;

    // if the disciminant is negative there wasn't a hit and as far as the sphere knows
    if (discriminant < 0) {
        return false;
    }

    // make sure that we only use rays that go away from the camera
    // we don't want to be able to see behind use

    float t = (-b - std::sqrt(discriminant));
    if (t < epsilon)
    {
        // if the first t was negative that means that it hit something behind us, we can now check
        // if the second point is also behind us
        t = (-b + std::sqrt(discriminant));
        if (t < epsilon)
            return false;
        // if the point isn't behind us we are inside the sphere so we tell our hit that.
        hit.front = false;
        // Rye::log("inside");
    }

    // otherwise calculate hit position
    hit.distance = t;
    hit.point = ray.at(t);
    hit.normal = (hit.point - transform.position) / transform.scale.x;

    return true;
}


bool Object::QuadHit(const Ray& ray, HitData& hit) const
{
    float a = glm::dot(m_planeNormal, ray.direction);

    // currently quads are infinetly thin os theres no reason to intersect their back.
    // if th ra direction and the plane normal don't point against each other then we would only hit the back
    if (a > 0)
        return false;

    float t = (m_planeOffset - glm::dot(m_planeNormal, ray.origin)) / a;

    if (t < epsilon)
        return false;

    glm::vec3 intersectionWorldSpace = ray.at(t);
    glm::vec3 intersectionPlanarWorldSpace = intersectionWorldSpace - transform.position;

    glm::vec2 intersectionPlanarSpace;
    intersectionPlanarSpace.x = glm::dot(glm::vec3(m_w), glm::cross(intersectionPlanarWorldSpace, glm::vec3(m_v)));
    intersectionPlanarSpace.y = glm::dot(glm::vec3(m_w), glm::cross(glm::vec3(m_u), intersectionPlanarWorldSpace));

    if (intersectionPlanarSpace.x < 0.0f || intersectionPlanarSpace.x > 1.0f || intersectionPlanarSpace.y < 0.0f || intersectionPlanarSpace.y > 1.0f)
        return false;

    hit.point = intersectionWorldSpace;
    hit.distance = t;
    hit.normal = m_planeNormal;
    hit.materialID = m_materialID;

    return true;
}
