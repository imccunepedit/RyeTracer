#ifndef SCENE_H_
#define SCENE_H_

#include <vector>

#include "Sphere.h"

class Scene {
    public:
        std::vector<Sphere> objects;
        void add_object(Sphere s);
};

#endif // SCENE_H_
