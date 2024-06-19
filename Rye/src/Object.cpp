#include "Object.h"

#include "Ray.h"

using namespace Rye;

bool Object::Hit(const Ray &ray, HitData& hit) const
{
    Ray localRay;
    localRay.direction = glm::vec3(transform.inverseMatrix * glm::vec4(ray.direction, 0));
    localRay.origin = glm::vec3(transform.inverseMatrix * glm::vec4(ray.origin, 1));

    hit.materialID = m_materialID;

    switch (objectType) {
        case Sphere:
            if (!SphereHit(localRay, hit))
                return false;

            break;

        case Quad:
            if (!QuadHit(localRay, hit))
                return false;
            break;

        default:
            return false;
    }

    // we need to renormalize the normal vector because the scaling of an object may have changed it
    // TODO figure out for plan and sphere if this can be done better
    hit.normal = glm::normalize(transform.matrix*glm::vec4(hit.normal,0));
    hit.point = ray.at(hit.distance);
    return true;
}

bool Object::SphereHit(const Ray& ray, HitData& hit) const
{
    float a = glm::dot(ray.direction, ray.direction);
    float inverse_a = 1/a;
    float b = glm::dot(ray.direction, ray.origin);
    float c = glm::dot(ray.origin, ray.origin) - 1;

    // calculate the discriminant
    float discriminant = b*b - a*c;

    // if the disciminant is negative there wasn't a hit and as far as the sphere knows
    if (discriminant < 0) {
        return false;
    }

    float min_t = 0.001;
    // make sure that we only use rays that go away from the camera
    // we don't want to be able to see behind use

    float t = (-b - std::sqrt(discriminant)) * inverse_a;
    if (t < min_t)
    {
        // if the first t was negative that means that it hit something behind us, we can now check
        // if the second point is also behind us
        t = (-b + std::sqrt(discriminant)) * inverse_a;
        if (t < min_t)
            return false;
        // if the point isn't behind us we are inside the sphere so we tell our hit that.
        hit.front = false;
    }

    // otherwise calculate hit position
    hit.distance = t;
    hit.normal = ray.at(t);

    return true;
}


bool Object::QuadHit(const Ray& ray, HitData& hit) const
{
    glm::vec3 n = glm::vec3(0,0,1);

    // our ray is pretty much parrallel to the plan so no intersections
    if (glm::abs(ray.direction.z) < 0.00001)
        return false;

    // if the ray starts above or below the surface and points away the return
    if (ray.origin.z * ray.direction.z > 0)
        return false;

    // otherwise calculate our t;
    float t = -ray.origin.z * 1/ray.direction.z;

    hit.point = ray.at(t);

    // we haven't hit inside the quad
    if (hit.point.x < 0.0f || hit.point.x > 1.0f || hit.point.y < 0.0f || hit.point.y > 1.0f)
        return false;

    hit.distance = t;
    hit.front = ray.direction.z < 0;
    hit.normal = glm::vec3(0,0,1);
    return true;
}
