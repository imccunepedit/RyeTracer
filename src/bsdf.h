#ifndef BSDF_H_
#define BSDF_H_

#include "Hit.h"
#include "Ray.h"
#include "Random.h"

#include <glm/geometric.hpp>
#include "imgui.h"
#include <glm/gtc/type_ptr.hpp>

class bsdf {
    public:
        virtual bool scatter(const Ray& in_ray, Hit& hit, Ray& scatter_ray) { return false; }

        virtual glm::vec3 emissive(const Ray& in_ray, Hit& hit) { return glm::vec3(0.0f); }

        virtual bool draw_attributes() { return false; }

};


class lambertian_bsdf : public bsdf {
    public:
        bool scatter(const Ray& in_ray, Hit& hit, Ray& scatter_ray) override
        {
            uint32_t seed = in_ray.seed;
            scatter_ray.origin = hit.point + hit.normal * 0.001f;
            scatter_ray.direction = glm::normalize(hit.normal + raytracing::random_on_sphere(seed));
            scatter_ray.seed = seed;
            hit.color = color;
            return true;
        }

        bool draw_attributes() override
        {
            ImGui::SetNextItemOpen(true, ImGuiCond_Once);
            if (ImGui::TreeNode("Diffuse bsdf"))
            {
                ImGui::ColorEdit3("Color", glm::value_ptr(color));
                ImGui::TreePop();
            }
            return true;
        }

    public:
        glm::vec3 color = glm::vec3(0.5f);

};


class metallic_bsdf : public bsdf {
    public:
        bool scatter(const Ray& in_ray, Hit& hit, Ray& scatter_ray) override
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
            if (ImGui::TreeNode("Metallic bsdf"))
            {
                ImGui::ColorEdit3("Color", glm::value_ptr(color));
                ImGui::TreePop();
            }
            return true;
        }
    public:
        glm::vec3 color = glm::vec3(1.0f);
};


class emission_bsdf : public bsdf {
    public:
        emission_bsdf();
        emission_bsdf(glm::vec3 color, float strength) : color(color), strength(strength) {}
        glm::vec3 emissive(const Ray& in_ray, Hit& hit) override
        {
            hit.color = glm::vec3(1);
            return color * strength;
        }

        bool draw_attributes() override
        {
            ImGui::SetNextItemOpen(true, ImGuiCond_Once);
            if (ImGui::TreeNode("Emission BSDF"))
            {
                ImGui::ColorEdit3("Color", glm::value_ptr(color));
                ImGui::DragFloat("Strength", &strength, 1.0f, 0.0f);
                ImGui::TreePop();
            }
            return true;
        }
    public:
        glm::vec3 color = glm::vec3(1.0f, 0.9f, 0.8f);
        float strength = 1.0f;
};


#endif // BSDF_H_
