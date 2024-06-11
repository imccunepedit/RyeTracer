#ifndef METALLIC_H_
#define METALLIC_H_

#include "../Material.h"
#include "../Hit.h"
#include "../Ray.h"
#include "../Random.h"

#include <glm/geometric.hpp>
#include "imgui.h"
#include <glm/gtc/type_ptr.hpp>

class metallic_bsdf : public Material {
    public:
        bool bsdf(const Ray &in_ray, Hit &hit, Ray &scatter_ray) override {
            uint32_t seed = in_ray.seed;
            scatter_ray.direction = glm::reflect(in_ray.direction, hit.normal) + raytracing::random_on_sphere(seed) * roughness;

            scatter_ray.origin = hit.point;
            scatter_ray.seed = seed;
            scatter_ray.normalize();
            hit.color = color;
            return true;
        }

        bool draw_attributes() override
        {
            ImGui::SetNextItemOpen(true, ImGuiCond_Once);
            if (ImGui::TreeNode("Metallic BSDF"))
            {
                ImGui::ColorEdit3("Color", glm::value_ptr(color));
                ImGui::DragFloat("Roughness", &roughness);
                ImGui::TreePop();
            }
            return true;
        }

    private:
        glm::vec3 color = glm::vec3(0.9f);
        float roughness = 0;
};



#endif // METALLIC_H_
