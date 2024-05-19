#include "Sphere.h"

bool Sphere::hit(Ray &ray, Hit &hit) {

    // calculate a b and c for the quadratic fomula
    // see docs/raytracing.org for explanation
    double a = glm::dot(ray.direction, ray.direction);
    double b = -2.0 * glm::dot(ray.direction, center - ray.origin);
    double c = glm::dot(center - ray.origin,center - ray.origin) - radius * radius;

    // calculate the discriminant
    double discriminant = b*b - 4*a*c;
    double t = -1.0;
    hit.point = ray.at(t);
    hit.normal = glm::normalize(hit.point - center);

    // if the disciminant is negative there wasn't a hit
    if (discriminant < 0) return false;

    // otherwise calculate hit position
    t = (-b - std::sqrt(discriminant)) / (2*a);
    hit.point = ray.at(t);

    return true;

}
