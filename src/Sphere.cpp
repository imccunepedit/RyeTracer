#include "Sphere.h"


Hit Sphere::hit(const Ray &ray) {

    // calculate a b and c for the quadratic fomula
    // see docs/raytracing.org for explanation
    float a = glm::dot(ray.direction, ray.direction);
    float b = 2.0 * glm::dot(ray.direction, ray.origin - center);
    float c = glm::dot(center - ray.origin,center - ray.origin) - radius * radius;

    // calculate the discriminant
    Hit hit;
    float discriminant = b*b - 4*a*c;

    // if the disciminant is negative there wasn't a hit and as far as the sphere knows
    if (discriminant < 0) {
        return hit;
    }


    // make sure that we only use rays that go away from the camera
    // we don't want to be able to see behind use
    float t = (-b - std::sqrt(discriminant)) / (2*a);
    if (t < 0)
        return hit;

    // otherwise calculate hit position
    hit.distance = t;
    hit.point = ray.at(t);
    hit.normal = (hit.point - center) / radius;
    hit.color = material.diffuse;

    return hit;

}
