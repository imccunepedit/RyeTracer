#ifndef LAMBERTIAN_H_
#define LAMBERTIAN_H_

#include "../Hit.h"
#include "../Ray.h"
#include "../Random.h"
#include "../Material.h"

#include <glm/geometric.hpp>
#include "imgui.h"
#include <glm/gtc/type_ptr.hpp>


class lambertian_bsdf : public Material {
    public:
        bool bsdf(const Ray& in_ray, Hit& hit, Ray& scatter_ray) override
        {
            uint32_t seed = in_ray.seed;
            scatter_ray.direction = hit.normal + raytracing::random_on_sphere(seed);

            scatter_ray.origin = hit.point;
            scatter_ray.seed = seed;
            scatter_ray.normalize();
            hit.color = color;
            return true;
        }

        bool draw_attributes() override
        {
            ImGui::SetNextItemOpen(true, ImGuiCond_Once);
            if (ImGui::TreeNode("Diffuse BSDF"))
            {
                ImGui::ColorEdit3("Color", glm::value_ptr(color), ImGuiColorEditFlags_Float);
                ImGui::TreePop();
            }
            return true;
        }

    private:
        glm::vec3 color = glm::vec3(0.5f);

};


#endif // LAMBERTIAN_H_
