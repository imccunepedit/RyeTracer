#include "Sphere.h"


Hit Sphere::hit(Ray &ray) {

    Hit hit;
    // calculate a b and c for the quadratic fomula
    // see docs/raytracing.org for explanation
    float a = glm::dot(ray.direction, ray.direction);
    float b = 2.0 * glm::dot(ray.direction, ray.origin - center);
    float c = glm::dot(center - ray.origin,center - ray.origin) - radius * radius;

    // calculate the discriminant
    float discriminant = b*b - 4*a*c;
    float t = -1.0;

    hit.t = t;

    // if the disciminant is negative there wasn't a hit
    if (discriminant < 0) {
        return hit;
    }

    hit.point = ray.at(t);
    hit.normal = glm::normalize(hit.point - center);
    hit.color = color;

    // otherwise calculate hit position
    t = (-b - std::sqrt(discriminant)) / (2*a);
    hit.point = ray.at(t);
    hit.t = t;

    return hit;

}
