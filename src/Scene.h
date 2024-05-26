#ifndef SCENE_H_
#define SCENE_H_

#include "glm/vec3.hpp"

#include <vector>
#include <memory>

#include "Sphere.h"
#include "Hit.h"
#include "Ray.h"

class Scene {
    public:
        void add_sphere(Sphere s);
        void remove_sphere(const int& i);
        void load_default();
        bool hit(const Ray& ray, Hit& hit) const;

    public:
        std::vector<Sphere> spheres;
        Material sky_material;
        glm::vec3 directional_light_direction = glm::vec3(0.0f,0.0f,0.0f);
        glm::vec3 directional_light_color = sky_material.emissive;
};

#endif // SCENE_H_
