#include "Object.h"

#include "Ray.h"

using namespace Rye;

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

    float min_t = 0.001;
    // make sure that we only use rays that go away from the camera
    // we don't want to be able to see behind use

    float t = (-b - std::sqrt(discriminant));
    if (t < min_t)
    {
        // if the first t was negative that means that it hit something behind us, we can now check
        // if the second point is also behind us
        t = (-b + std::sqrt(discriminant));
        if (t < min_t)
            return false;
        // if the point isn't behind us we are inside the sphere so we tell our hit that.
        hit.front = false;
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

    if (std::abs(a) < 0.00001)
    {
        return false;
    }

    float t = (m_planeOffset - glm::dot(m_planeNormal, ray.origin)) / a;

    float min_t = 0.0001;
    if (t < min_t)
        return false;

    glm::vec3 intersectionWorldSpace = ray.at(t);
    glm::vec3 intersectionPlanarWorldSpace = intersectionWorldSpace - transform.position;

    glm::vec2 intersectionPlanarSpace;
    intersectionPlanarSpace.x = glm::dot(glm::vec3(m_w), glm::cross(intersectionPlanarWorldSpace, glm::vec3(m_v)));
    intersectionPlanarSpace.y = glm::dot(glm::vec3(m_w), glm::cross(glm::vec3(m_u), intersectionPlanarWorldSpace));

    if (intersectionPlanarSpace.x < 0.0f || intersectionPlanarSpace.x > 1.0f || intersectionPlanarSpace.y < 0.0f || intersectionPlanarSpace.y > 1.0f)
        return false;

    hit.point = intersectionWorldSpace;
    hit.front = true;
    hit.distance = t;
    hit.normal = m_planeNormal;
    hit.materialID = m_materialID;

    return true;
}
