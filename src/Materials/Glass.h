#ifndef GLASS_H_
#define GLASS_H_


#include "../Hit.h"
#include "../Ray.h"
#include "../Random.h"
#include "../Material.h"

#include <glm/geometric.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui.h"

class glass_bsdf : public Material {
    public:
        bool bsdf(const Ray& in_ray, Hit& hit, Ray& scatter_ray) override
        {
            uint32_t seed = in_ray.seed;
            float eta = 1/ior;
            float at = 1;
            hit.color = glm::vec3(1);

            hit.normal += raytracing::random_on_sphere(seed) * roughness;
            hit.normal = glm::normalize(hit.normal);

            if (hit.inside)
            {
                eta = 1/eta;
                hit.normal *= -1;
                hit.color = glm::pow(color, glm::vec3(hit.distance));
            }

            scatter_ray.direction = glm::refract(in_ray.direction, hit.normal, eta);
            bool reflect = glm::dot(scatter_ray.direction, scatter_ray.direction) < 0.1;

            float cos_angle = glm::dot(in_ray.direction, -hit.normal);
            float r0 = (1-eta) / (1+eta);
            float schlick = r0 + (1-r0)*pow((1 - cos_angle),5);
            reflect |= schlick > raytracing::random_float(seed);

            if (reflect)
                scatter_ray.direction = glm::reflect(in_ray.direction, hit.normal);


            scatter_ray.origin = hit.point;
            scatter_ray.seed = seed;
            scatter_ray.normalize();
            return true;
        }

        bool draw_attributes() override
        {
            ImGui::SetNextItemOpen(true, ImGuiCond_Once);
            if (ImGui::TreeNode("Glass BSDF"))
            {
                ImGui::ColorEdit3("Color", glm::value_ptr(color));
                ImGui::DragFloat("IoR", &ior);
                ImGui::DragFloat("Roughness", &roughness);
                ImGui::TreePop();
            }
            return true;
        }

    private:
        glm::vec3 color = glm::vec3(1.0f);
        float ior = 1.5f;
        float roughness = 0;

};



#endif // GLASS_H_
