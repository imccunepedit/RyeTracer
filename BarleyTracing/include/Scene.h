#ifndef SCENE_H_
#define SCENE_H_

#include "glm/vec4.hpp"

#include <vector>
#include <memory>

#include "Object.h"

#include "HitData.h"
#include "Ray.h"
#include "Material.h"

class Scene {
    public:
        void AddObject(std::shared_ptr<Object> o);
        void RemoveObject(const int& i);

        void AddMaterial(std::shared_ptr<Material> m);
        void RemoveMaterial(const int& i);

        void Initialize();
        bool Hit(const Ray& ray, HitData& hit) const;

    public:
        std::vector<std::shared_ptr<Object>> objects;
        std::vector<std::shared_ptr<Material>> materials;
        size_t materialCount = 0;

        glm::vec3 ambientColor = glm::vec3(0.0f);

        glm::vec3 lightDirection = glm::vec3(1.0f,0.0f,-1.0f);
        glm::vec3 lightColor = glm::vec3(1.0f,0.8f,0.6f);
};

#endif // SCENE_H_
