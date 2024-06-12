#ifndef GLOSSY_H_
#define GLOSSY_H_

#include <string>

#include "../Hit.h"
#include "../Ray.h"
#include "../Random.h"
#include "../Material.h"
#include "Lambertian.h"
#include "Specular.h"

#include <glm/geometric.hpp>
#include "imgui.h"
#include <glm/gtc/type_ptr.hpp>


class glossy_bsdf : public Material {
    public:
        bool bsdf(const Ray& in_ray, Hit& hit, Ray& scatter_ray) override
        {
            uint32_t seed = in_ray.seed;
            if (raytracing::random_float(seed) > specular_prob)
            {
                diffuse.bsdf(in_ray, hit, scatter_ray);
                return true;
            }
            spec.bsdf(in_ray, hit, scatter_ray);
            return true;
        }

        bool draw_attributes() override
        {
            diffuse.draw_attributes();
            spec.draw_attributes();
            ImGui::DragFloat("Specular probability", &specular_prob, 0.01f, 0,1);
            return true;
        }

        std::string get_name() override
        {
            return "Glossy BSDF";
        }

    private:
        lambertian_bsdf diffuse;
        specular_bsdf spec;
        float specular_prob = 0.8;

};

#endif // GLOSSY_H_
