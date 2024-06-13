#ifndef EMISSION_H_
#define EMISSION_H_

#include <string>

#include "Hit.h"
#include "Ray.h"
#include "Random.h"
#include "Material.h"

#include <glm/geometric.hpp>
#include "imgui.h"
#include <glm/gtc/type_ptr.hpp>



class emission : public Material {
    public:
        emission() {};
        emission(glm::vec3 color, float strength) : color(color), strength(strength) {}
        bool absorb(const Ray& in_ray, Hit& hit) override
        {
            hit.color = color * strength;
            return true;
        }

        bool draw_attributes() override
        {
            ImGui::ColorEdit3("Color", glm::value_ptr(color), ImGuiColorEditFlags_Float);
            ImGui::DragFloat("Strength", &strength, 1.0f, 0.0f);
            return true;
        }

        std::string get_name() override
        {
            return "Emmisive";
        }
    private:
        glm::vec3 color = glm::vec3(1.0f, 0.9f, 0.8f);
        float strength = 10.0f;
};


#endif // EMISSION_H_
