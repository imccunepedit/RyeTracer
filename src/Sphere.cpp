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
    float t = -1.0f;


    // if the disciminant is negative there wasn't a hit and as far as the sphere knows
    // the ray went to infinity (or the sky box) so we can say that the normal is pointing
    // back at the camera
    if (discriminant < 0) {
        hit.t = t;
        hit.point = ray.at(t);
        hit.normal = -ray.direction;
        return hit;
    }


    // otherwise calculate hit position
    t = (-b - std::sqrt(discriminant)) / (2*a);
    hit.t = t;
    hit.point = ray.at(t);
    hit.normal = (hit.point - center) / radius;
    hit.color = material.diffuse;

    return hit;

}
