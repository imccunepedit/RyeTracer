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
            scatter_ray.origin = hit.point + hit.normal * 0.001f;
            scatter_ray.direction = glm::normalize(glm::reflect(in_ray.direction, hit.normal) + raytracing::random_on_sphere(seed) * m_roughness);
            scatter_ray.seed = seed;
            hit.color = m_color;
            return true;
        }

        bool draw_attributes() override
        {
            ImGui::SetNextItemOpen(true, ImGuiCond_Once);
            if (ImGui::TreeNode("Metallic BSDF"))
            {
                ImGui::ColorEdit3("Color", glm::value_ptr(m_color));
                ImGui::DragFloat("Roughness", &m_roughness);
                ImGui::TreePop();
            }
            return true;
        }

    private:
        glm::vec3 m_color = glm::vec3(1.0f);
        float m_roughness = 0;
};



#endif // METALLIC_H_
