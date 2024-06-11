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
                hit.color = color;
            }

            scatter_ray.direction = glm::refract(in_ray.direction, hit.normal, eta);
            bool reflect = glm::dot(scatter_ray.direction, scatter_ray.direction) < 0.1;

            reflect |= fresnel(in_ray.direction, hit.normal, eta) > raytracing::random_float(seed);
            // hit.color = glm::vec3(fresnel(in_ray.direction, hit.normal, eta));
            // return false;

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
                ImGui::DragFloat("IoR", &ior, 0.01f, 0.0f);
                ImGui::DragFloat("Roughness", &roughness, 0.1f, 0, 1);
                ImGui::Checkbox("correctness", &correctness);
                ImGui::TreePop();
            }
            return true;
        }


        float fresnel(glm::vec3 I, glm::vec3 N, float n1)
        {
            float n2 = 1;
            float c1 = glm::dot(I,-N);
#ifndef SCHLICK
            float c2 = sqrtf(1 - (n1*n1/(n2*n2)) * (1- (c1*c1)));
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

    private:
        glm::vec3 color = glm::vec3(1.0f);
        float ior = 1.5f;
        float roughness = 0;
        bool correctness = true;

};



#endif // GLASS_H_
