#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <string>

#include "imgui.h"

#include <glm/geometric.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "HitData.h"
#include "Ray.h"
#include "Utils.h"


class Material {
    public:
        virtual bool BSDF(const Ray& inRay, HitData& hit, Ray& scatterRay) { return false; }

        virtual bool Absorb(const Ray& inRay, HitData& hit) { return false; } // technically emitting and being absorbed into camera but we are being backwards

        virtual bool DrawAttributes() { return false; }
        virtual std::string GetName() = 0;

    // private:
        float Fresnel(glm::vec3 I, glm::vec3 N, float n1)
        {
            float n2 = 1;
            float c1 = glm::dot(I,-N);
#ifndef SCHLICK
            float c2 = sqrtf(1 - n1*n1/(n2*n2) * (1- c1*c1));
            float Rs = (n1*c1 - n2*c2) / (n1*c1 + n2*c2);
            float Rp = (n1*c2 - n2*c1) / (n1*c2 + n2*c1);
            return 0.5 * (Rs*Rs + Rp*Rp);
#else
            float n12 = n1-n2;
            float R0 = n12 / (n1+n2);
            R0 *= R0;
            return R0 + (1-R0)*pow((1 - c1),5);
#endif
        }
};

#endif // MATERIAL_H_
