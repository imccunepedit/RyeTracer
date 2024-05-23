#ifndef SCENE_H_
#define SCENE_H_

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
        Hit hit(const Ray& ray) const;

    public:
        std::vector<Sphere> spheres;
        glm::vec4 sky_color = {0.02,0.01,0.09,1.0}; //ambient lighting
        glm::vec3 directional_light = glm::vec3(0.0f,0.0f,0.0f);
};

#endif // SCENE_H_
