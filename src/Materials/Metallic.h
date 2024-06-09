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
        bool bsdf(const Ray& in_ray, Hit& hit, Ray& scatter_ray) override
        {
            scatter_ray.origin = hit.point + hit.normal * 0.001f;
            scatter_ray.direction = glm::reflect(in_ray.direction, hit.normal);
            scatter_ray.seed = in_ray.seed;
            hit.color = color;
            return true;
        }

        bool draw_attributes() override
        {
            ImGui::SetNextItemOpen(true, ImGuiCond_Once);
            if (ImGui::TreeNode("Metallic BSDF"))
            {
                ImGui::ColorEdit3("Color", glm::value_ptr(color));
                ImGui::TreePop();
            }
            return true;
        }

    public:
        glm::vec3 color = glm::vec3(1.0f);
};



#endif // METALLIC_H_
