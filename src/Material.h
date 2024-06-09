#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "Hit.h"
#include "Ray.h"
#include "Random.h"

#include <glm/geometric.hpp>
#include "imgui.h"
#include <glm/gtc/type_ptr.hpp>

class Material {
    public:
        virtual bool bsdf(const Ray& in_ray, Hit& hit, Ray& scatter_ray) { return false; }

        virtual bool absorb(const Ray& in_ray, Hit& hit) { return false; } // technically emitting and being absorbed into camera but we are being backwards

        virtual bool draw_attributes() { return false; }

};

#endif // MATERIAL_H_
