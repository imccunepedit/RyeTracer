#ifndef BSDF_H_
#define BSDF_H_

#include "Hit.h"
#include "Ray.h"
#include "Random.h"

#include "glm/geometric.hpp"

class bsdf {
    public:
        virtual bool scatter(const Ray& in_ray, Hit& hit, Ray& scatter_ray)
        {
            return false;
        }
};



class lambertian_bsdf : public bsdf {
    public:
        bool scatter(const Ray& in_ray, Hit& hit, Ray& scatter_ray) override
        {
            scatter_ray.origin = hit.point + hit.normal * 0.001f;
            scatter_ray.direction = glm::normalize(hit.normal + raytracing::random_on_sphere(hit.rseed));
            return true;
        }
};




#endif // BSDF_H_
