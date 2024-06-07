#include "Sphere.h"


bool Sphere::hit(const Ray &ray, Hit& hit) {

    // calculate a b and c for the quadratic fomula
    // see docs/raytracing.org for explanation
    //
    // since the ray direction should be normalized a should always be equal to 1
    // float a = glm::dot(ray.direction, ray.direction);
    float b = 2.0 * glm::dot(ray.direction, ray.origin - center);
    float c = glm::dot(center - ray.origin,center - ray.origin) - radius * radius;

    // calculate the discriminant
    float discriminant = b*b - 4*c;

    // if the disciminant is negative there wasn't a hit and as far as the sphere knows
    if (discriminant < 0) {
        return false;
    }


    // make sure that we only use rays that go away from the camera
    // we don't want to be able to see behind use
    float t = (-b - std::sqrt(discriminant)) * 0.5f;
    if (t < 0)
    {
        // if the first t was negative that means that it hit something behind us, we can now check
        // if the second point is also behind us
        float t = (-b + std::sqrt(discriminant)) * 0.5f;
        if (t < 0)
            return false;
        // if the point isn't behind us we are inside the sphere so we tell our hit that.
        hit.inside = true;
    }

    // otherwise calculate hit position
    hit.distance = t;
    hit.point = ray.at(t);
    hit.normal = (hit.point - center) / radius;
    hit.material = material;
    hit.material_id = material_id;

    return true;

}
