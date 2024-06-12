#ifndef SPECULAR_H_
#define SPECULAR_H_

#include <string>


#include "../Hit.h"
#include "../Ray.h"
#include "../Random.h"
#include "../Material.h"

#include <glm/geometric.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui.h"

class specular_bsdf : public Material {
    public:
        bool bsdf(const Ray& in_ray, Hit& hit, Ray& scatter_ray) override
        {
            uint32_t seed = in_ray.seed;

            hit.color = color;
            scatter_ray.direction = glm::reflect(in_ray.direction, hit.normal) + raytracing::random_on_sphere(seed) * roughness;

            scatter_ray.origin = hit.point;
            scatter_ray.seed = seed;
            scatter_ray.normalize();
            return true;
        }

        bool draw_attributes() override
        {
            ImGui::PushID((int*) "specular");
            ImGui::ColorEdit3("Color", glm::value_ptr(color), ImGuiColorEditFlags_Float);
            ImGui::DragFloat("Roughness", &roughness, 0.01f, 0, 1);
            ImGui::PopID();
            return true;
        }

        std::string get_name() override
        {
            return "Specular BSDF";
        }


    private:
        glm::vec3 color = glm::vec3(1);
        float roughness = 0;

};



#endif // SPECULAR_H_
