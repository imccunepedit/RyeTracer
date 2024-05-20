#ifndef SCENE_H_
#define SCENE_H_

#include <vector>
#include <memory>

#include "Sphere.h"

class Scene {
    public:
        void add_sphere(Sphere s);

    public:
        std::vector<Sphere> spheres;
        glm::vec4 sky_color = {0.02,0.01,0.09,1.0};
};

#endif // SCENE_H_
