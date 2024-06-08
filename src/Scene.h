#ifndef SCENE_H_
#define SCENE_H_

#include "glm/vec3.hpp"

#include <vector>
#include <memory>

#include "Object.h"
#include "Hit.h"
#include "Ray.h"
#include "bsdf.h"

class Scene {
    public:
        void add_object(std::shared_ptr<Object> o);
        void remove_object(const int& i);

        void add_material(std::shared_ptr<bsdf> m);
        void remove_material(const int& i);

        void load_default();
        bool hit(const Ray& ray, Hit& hit) const;

    public:
        std::vector<std::shared_ptr<Object>> objects;
        std::vector<std::shared_ptr<bsdf>> materials;
        size_t material_count = 0;

        glm::vec3 ambient_color = glm::vec3(0.0f);

        // glm::vec3 light_direction = glm::vec3(1.0f,0.0f,-1.0f);
        // glm::vec3 light_color = glm::vec3(1.0f,0.8f,0.6f);
};

#endif // SCENE_H_
